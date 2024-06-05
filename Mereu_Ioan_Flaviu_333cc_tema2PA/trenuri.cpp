#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// Variabile globale
unordered_map<string, int>
    cityToIndex;            // Pentru a mapea numele orașelor la indici
vector<vector<int>> graph;  // Graful
vector<int> inDegree;       // Numarul de noduri de intrare pentru fiecare nod
vector<int> maxCities;  // Nr max de orase vizitate pentru fiecare nod
vector<int> topoOrder;  // Ordinea topologica a nodurilor
string startCity, endCity;
// Functia pentru sortarea topologica folosind DFS
void topologicalSortDFS() {
    vector<bool> visited(graph.size(), false);  // Vector de vizitare
    stack<int> s;                               // Stiva pentru sortare

    // Funcția DFS
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;  // Marcam nodul ca vizitat
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
        s.push(
            node);  // Adaug nodul in stiva după vizitarea tuturor vecinilor
    };

    dfs(cityToIndex[startCity]);

    // Mut elementele din stiva în ordinea topologicas
    while (!s.empty()) {
        topoOrder.push_back(s.top());
        s.pop();
    }
}

int main() {
    ifstream fin("trenuri.in");
    ofstream fout("trenuri.out");

    fin >> startCity >> endCity;

    int M;
    fin >> M;

    // Citim datele de input construim graful
    int index = 0;
    for (int i = 0; i < M; ++i) {
        string city1, city2;
        fin >> city1 >> city2;
        if (cityToIndex.find(city1) == cityToIndex.end()) {
            cityToIndex[city1] = index++;
            graph.emplace_back();
            inDegree.push_back(0);
            maxCities.push_back(0);
        }
        if (cityToIndex.find(city2) == cityToIndex.end()) {
            cityToIndex[city2] = index++;
            graph.emplace_back();
            inDegree.push_back(0);
            maxCities.push_back(0);
        }
        graph[cityToIndex[city1]].push_back(cityToIndex[city2]);
        // Incrementwz gradul de intrare pentru orasul destinatar
        inDegree[cityToIndex[city2]]++;
    }

    // Sortam topologic folosind DFS si actualizam numarul maxim de oraae
    topologicalSortDFS();

    // Programare dinamica
    for (size_t i = 0; i < topoOrder.size(); ++i) {
        int node = topoOrder[i];
        // Actualiz pentru fiecare oraa vecin nr max de orase
        for (int neighbor : graph[node]) {
            maxCities[neighbor] = max(maxCities[neighbor], maxCities[node] + 1);
        }
    }

    // Gasesc indicele orasului destinatie si afisez nr max de orase
    // vizitate
    fout << maxCities[cityToIndex[endCity]] + 1 << endl;

    fin.close();
    fout.close();

    return 0;
}
