#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Deschiderea fișierului de intrare
    freopen("compresie.in", "r", stdin);

    // Citirea datelor de intrare
    int n, m;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }
    cin >> m;
    vector<int> B(m);
    for (int i = 0; i < m; ++i) {
        cin >> B[i];
    }

    // Parcurgere simultană și comparare a celor doi vectori
    int i = 0, j = 0, result = 0;
    while (i < n && j < m) {
        if (A[i] == B[j]) {
            ++i;
            ++j;
            ++result;  // cresc lungimea maximă a șirului rezultat
        } else if (A[i] < B[j]) {
            A[i + 1] += A[i];  // adun elementul mai mic la poziția următoare
            ++i;
        } else {
            B[j + 1] += B[j];
            ++j;
        }
    }

    // nu sunt siruri egale daca unul s-a terminat
    if (i < n || j < m) {
        result = -1;
    }

    fclose(stdin);

    // Deschiderea fișierului de ieșire și scrierea rezultatului
    freopen("compresie.out", "w", stdout);
    cout << result << "\n";
    fclose(stdout);

    return 0;
}
