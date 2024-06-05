#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

struct Node {
    set<int> connections;
    int discovery_time = -1;
    int lowest_time = -1;
    bool is_in_stack = false;
    bool assigned = false;
    bool value = false;
};

class Graph {
 public:
    explicit Graph(int variables) : nodes_(2 * variables) {}

    int Variables() const {
        return nodes_.size() / 2;
    }

    void AddImplication(int a, int b) {
        nodes_[Index(a)].connections.insert(b);
        nodes_[Index(-b)].connections.insert(-a);
    }

    Node& operator[](int index) {
        return nodes_[Index(index)];
    }

    const Node& operator[](int index) const {
        return nodes_[Index(index)];
    }

 private:
    vector<Node> nodes_;

    int Index(int index) const {
        return index > 0 ? index - 1 : nodes_.size() + index;
    }
};

void ExtractComponent(Graph& graph, int end_node, stack<int>& node_stack,
                      vector<int>& order) {
    while (order.empty() || order.back() != end_node) {
        int node = node_stack.top();
        node_stack.pop();
        graph[node].is_in_stack = false;
        order.push_back(node);
    }
}

void TarjanSCC(Graph& graph, int node, stack<int>& node_stack,
               vector<int>& order) {
    static int current_time = 0;
    graph[node].discovery_time = graph[node].lowest_time = ++current_time;
    node_stack.push(node);
    graph[node].is_in_stack = true;

    for (const auto& neighbor : graph[node].connections) {
        if (graph[neighbor].discovery_time == -1) {
            TarjanSCC(graph, neighbor, node_stack, order);
            graph[node].lowest_time = min(graph[node].lowest_time,
                                          graph[neighbor].lowest_time);
        } else if (graph[neighbor].is_in_stack) {
            graph[node].lowest_time = min(graph[node].lowest_time,
                                          graph[neighbor].discovery_time);
        }
    }

    if (graph[node].lowest_time == graph[node].discovery_time) {
        ExtractComponent(graph, node, node_stack, order);
    }
}

vector<int> DetermineOrder(Graph& graph) {
    vector<int> order;
    for (int i = 1; i <= graph.Variables(); ++i) {
        if (graph[i].discovery_time == -1) {
            stack<int> node_stack;
            TarjanSCC(graph, i, node_stack, order);
        }
        if (graph[-i].discovery_time == -1) {
            stack<int> node_stack;
            TarjanSCC(graph, -i, node_stack, order);
        }
    }
    reverse(order.begin(), order.end());
    return order;
}

vector<int> Solve2SAT(Graph& graph) {
    for (const auto& node : DetermineOrder(graph)) {
        if (!graph[node].assigned) {
            graph[node].value = false;
            graph[node].assigned = true;
            graph[-node].value = true;
            graph[-node].assigned = true;
        }
    }

    vector<int> result;
    for (int i = 1; i <= graph.Variables(); ++i) {
        if (graph[i].value) {
            result.push_back(i);
        }
    }
    return result;
}

int main() {
    ifstream input("scandal.in");
    ofstream output("scandal.out");

    int variables, conditions;
    input >> variables >> conditions;

    Graph graph(variables);
    for (int i = 0; i < conditions; ++i) {
        int a, b, type;
        input >> a >> b >> type;

        if (type == 0) {
            graph.AddImplication(-a, b);
        } else if (type == 1) {
            graph.AddImplication(-a, -b);
        } else if (type == 2) {
            graph.AddImplication(-b, -a);
        } else if (type == 3) {
            graph.AddImplication(a, -b);
        }
    }

    auto result = Solve2SAT(graph);
    output << result.size() << "\n";
    for (const auto& node : result) {
        output << node << "\n";
    }
    return 0;
}
