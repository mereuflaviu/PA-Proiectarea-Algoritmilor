#include <algorithm>
#include <bitset>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int nmax = 1e5;
const long long val_mare = 1e10;
int n;

void init(long long val, long long dist[]) {
    for (int i = 1; i <= n; ++i) dist[i] = val;
}

void dijkstra(int start, vector<pair<int, int>> graf[], long long d[]) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    d[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;

        pq.pop();

        if (dist > d[node]) continue;

        for (auto muchie : graf[node]) {
            int vecin = muchie.first;
            int cost = muchie.second;

            if (d[node] + cost < d[vecin]) {
                d[vecin] = d[node] + cost;
                pq.push({d[vecin], vecin});
            }
        }
    }
}

int main() {
    ifstream fin("drumuri.in");
    ofstream fout("drumuri.out");

    int m, u, v, c, x, y, z;
    vector<pair<int, int>> graf[nmax + 1];
    vector<pair<int, int>> transpus[nmax + 1];
    fin >> n >> m;

    for (int i = 0; i < m; ++i) {
        fin >> u >> v >> c;
        graf[u].push_back({v, c});
        transpus[v].push_back({u, c});
    }

    fin >> x >> y >> z;
    // CAZUL GENERAL DE ANALIZAT CU T DE LA 1 LA N(t = x, t = y, t = z sunt cele
    // normale)
    /* x\
        t->z
       y/
    */
    long long dist_x[nmax + 1];
    init(val_mare, dist_x);
    dijkstra(x, graf, dist_x);

    long long dist_y[nmax + 1];
    init(val_mare, dist_y);
    dijkstra(y, graf, dist_y);

    long long dist_z[nmax + 1];
    init(val_mare, dist_z);
    dijkstra(z, transpus, dist_z);
    long long ans = dist_x[1] + dist_y[1] + dist_z[1];
    for (int i = 2; i <= n; ++i) {
        ans = min(ans, dist_x[i] + dist_y[i] + dist_z[i]);
    }

    fout << ans;
    fin.close();
    fout.close();

    return 0;
}
