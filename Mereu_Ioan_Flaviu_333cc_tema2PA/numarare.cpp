#include <bits/stdc++.h>

using namespace std;

int numVertices, numEdges;
vector<vector<int>> graphAdjList;

#define mod 1000000007

// Iterative DFS function used for topological sorting
void dfs(int start, vector<bool>& visited, stack<int>& nodeStack) {
  stack<int> tempStack;
  tempStack.push(start);

  while (!tempStack.empty()) {
    int current = tempStack.top();
    if (!visited[current]) {
      visited[current] = true;
      // Visit all neighbors of the current node
      for (int i = 0; i < (int)graphAdjList[current].size(); i++) {
        int neighbor = graphAdjList[current][i];
        if (!visited[neighbor]) {
          tempStack.push(neighbor);
        }
      }
    } else {
      tempStack.pop();
      nodeStack.push(current);  // Add to the topological order
    }
  }
}

// Function to perform topological sort
vector<int> topological_sort() {
  stack<int> nodeStack;
  vector<int> topologicalOrder;
  vector<bool> visited(numVertices + 1, false);

  // Perform DFS for each unvisited node
  for (int i = 1; i <= numVertices; i++) {
    if (!visited[i]) {
      dfs(i, visited, nodeStack);
    }
  }

  // Extract nodes from stack to form the topological order
  while (!nodeStack.empty()) {
    topologicalOrder.push_back(nodeStack.top());
    nodeStack.pop();
  }

  return topologicalOrder;
}

// Function to count all paths from node src to node dest using dynamic
// programming
long long count_paths(int src, int dest) {
  vector<int> topoOrder = topological_sort();
  vector<long long> pathCount(numVertices + 1, 0);
  pathCount[src] = 1;  // Start node has value 1

  // Calculate number of paths in topological order
  for (int i = 0; i < numVertices; i++) {
    int node = topoOrder[i];
    if (pathCount[node] > 0) {
      for (int j = 0; j < (int)graphAdjList[node].size(); j++) {
        int neighbor = graphAdjList[node][j];
        pathCount[neighbor] = (pathCount[neighbor] + pathCount[node]) % mod;
      }
    }
  }
  return pathCount[dest];
}

int main() {
  std::ifstream fin("numarare.in");
  std::ofstream fout("numarare.out");
  fin >> numVertices >> numEdges;
  graphAdjList.resize(numVertices + 1);

  vector<pair<int, int>> edgesFirstGraph(numEdges);
  vector<pair<int, int>> edgesSecondGraph(numEdges);

  // Read edges of the first graph
  for (int i = 0; i < numEdges; i++) {
    int from, to;
    fin >> from >> to;
    edgesFirstGraph[i] = {from, to};
  }

  // Read edges of the second graph
  for (int i = 0; i < numEdges; i++) {
    int from, to;
    fin >> from >> to;
    edgesSecondGraph[i] = {from, to};
  }

  // Store edges of the first graph in a map for quick lookup
  unordered_map<int, unordered_set<int>> edgeMap;
  for (const auto& edge : edgesFirstGraph) {
    edgeMap[edge.first].insert(edge.second);
  }

  // Find common edges between the two graphs
  vector<pair<int, int>> commonEdges;
  for (const auto& edge : edgesSecondGraph) {
    if (edgeMap[edge.first].count(edge.second)) {
      commonEdges.push_back(edge);
    }
  }

  // Add common edges to the adjacency list of the graph
  for (const auto& edge : commonEdges) {
    graphAdjList[edge.first].push_back(edge.second);
  }

  // Print the number of paths from node 1 to node n in the common graph
  fout << count_paths(1, numVertices);

  return 0;
}
