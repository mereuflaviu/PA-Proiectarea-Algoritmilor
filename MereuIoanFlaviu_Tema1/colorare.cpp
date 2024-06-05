#include <iostream>
#include <fstream>

const int MOD = 1e9 + 7;

// funcție pentru efectuarea ridicării la putere
long long powMod(long long base, long long exp) {
    long long result = 1;
    base %= MOD;  // baza se află în intervalul modulo

    while (exp > 0) {
        if (exp & 1) {  // verific dacă exp este impar
            result = (result * base) % MOD;  // calculul eficient al puterii
        }
        base = (base * base) % MOD;  // ridicare la patrat
        exp >>= 1;  // impartire efectuata prin deplasare a bitului la dreapta
    }

    return result;
}

int main() {
    std::ifstream fin("colorare.in");
    std::ofstream fout("colorare.out", std::ios::out);

    int K;
    fin >> K;

    char lastType = ' ';
    long long ways = 1;

    for (int i = 0; i < K; ++i) {
        int X;
        char T;
        fin >> X >> T;

        long long currentWays = 1;

        if (T == 'V') {
            if (lastType == ' ') {
                currentWays = (3 * powMod(2, X - 1)) % MOD;
            } else if (lastType == 'V') {
                currentWays = powMod(2, X) % MOD;
            } else if (lastType == 'H') {
                currentWays = powMod(2, X - 1) % MOD;
            }
        } else if (T == 'H') {
            if (lastType == ' ') {
                currentWays = (6 * powMod(3, X - 1)) % MOD;
                // calculul pt lastType = ' '

            } else if (lastType == 'H') {
                currentWays = powMod(3, X) % MOD;
            } else if (lastType == 'V') {
                currentWays = (2 * powMod(3, X - 1)) % MOD;
            }
        }

        lastType = T;
        ways = (ways * currentWays) % MOD;  // update total nr cai
    }

    fout << ways;

    fin.close();
    fout.close();
    return 0;
}
