#include <String>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;



float P[11] = {0,
               0.214,
               0.143,
               0.071,
               0.071,
               0.071,
               0.071,
               0.071,
               0.071,
               0.071,
               0.071};
float Q[11] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
};
int C[11][11];
int S[11];
int n = 10;
float Length[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float Sl = 0;
float Sr = 0;

float q = 0;
int Len = 0;
float Entropy = 0;

void shenon()
{
    float P[11] = {0,
                   0.214,
                   0.143,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071};
    float Q[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float L[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int C[11][11];
    int n = 10;
    float srLen = 0;

    for (int i = 0; i <= n; i++) {
        Q[i] = 0;
        L[i] = 0;
        for (int j = 0; j <= n; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        Q[i] = Q[i - 1] + P[i];
        L[i] = ceil(log2(1 / P[i]));
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= L[i]; j++) {
            Q[i - 1] *= 2;

            C[i][j] = floor(Q[i - 1]);

            if (Q[i - 1] >= 1) {
                Q[i - 1] = Q[i - 1] - 1;
            }
        }
    }
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j <= L[i]; j++) {
            cout << C[i][j];
        }
        cout << " Длина: " << L[i] << " Вероятность: " << P[i] << endl;
        srLen += L[i] * P[i];
    }
    cout << endl << "Lcp: " << srLen << endl;
    for (int i = 1; i < n; i++) {
        Entropy -= P[i] * log2(P[i]);
    }
    cout << "Энтропия: " << Entropy << endl << endl;
}

void gilbert()
{
    float P[11] = {0,
                   0.071,
                   0.143,
                   0.214,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071,
                   0.071};
    float Q[11];
    float L[11];
    int C[11][11];
    int n = 10;
    float srLen = 0;

    for (int i = 0; i <= n; i++) {
        Q[i] = 0;
        L[i] = 0;
        for (int j = 0; j <= n; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == i) {
                Q[i] += P[j] / 2;
            } else {
                Q[i] += P[j];
            }
        }
        L[i] = ceil(log2(1 / P[i])) + 1;
    }

    int k = 2;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= L[i]; j++) {
            Q[k - 1] *= 2;

            C[i][j] = floor(Q[k - 1]);

            if (Q[k - 1] >= 1) {
                Q[k - 1] = Q[k - 1] - 1;
            }
        }
        k++;
    }
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j <= L[i]; j++) {
            cout << C[i][j];
        }
        cout << " Длина: " << L[i] << " Вероятность: " << P[i] << endl;
        srLen += L[i] * P[i];
    }
    cout << endl << "Lcp: " << srLen << endl;
    for (int i = 1; i < n; i++) {
        Entropy -= P[i] * log2(P[i]);
    }
    cout << "Энтропия: " << Entropy << endl << endl;
}

int Med(int L, int R, float P[])
{
    int m = 0, i = 0;
    Sl = 0;
    m = 0;
    for (i = L; i <= R - 1; i++) {
        Sl += P[i];
    }
    Sr = P[R];
    m = R;
    while (Sl >= Sr) {
        m--;
        Sl -= P[m];
        Sr += P[m];
    }
    return m;
}

void fano(int L, int R, int k)
{
    float srLen = 0;
    int m = 0, i = 0;
    if (L < R) {
        k++;
        m = Med(L, R, P);
        for (i = L; i <= R; i++) {
            if (i <= m) {
                C[i][k] = 0;
                Length[i]++;
            } else {
                C[i][k] = 1;
                Length[i]++;
            }
        }
        fano(L, m, k);
        fano(m + 1, R, k);
    }
}

int Up(int n, float q)
{
    int j = 1;
    for (int i = n - 1; i >= 2; i--) {
        if (P[i - 1] <= q) {
            P[i] = P[i - 1];
        } else {
            j = i;
            break;
        }
    }
    P[j] = q;
    return j;
}

void Down(int n, int j)
{
    int S[11];

    for (int i = 1; i < 11; i++) {
        S[i] = C[j][i];
    }
    Len = Length[j];
    for (int i = j; i <= n - 2; i++) {
        for (int k = 1; k < 11; k++) {
            C[i][k] = C[i + 1][k];
        }
        Length[i] = Length[i + 1];
    }

    for (int i = 1; i < 11; i++) {
        C[n - 1][i] = S[i];
        C[n][i] = S[i];
    }
    C[n - 1][Len + 1] = 0;
    C[n][Len + 1] = 1;
    Length[n - 1] = Len + 1;
    Length[n] = Len + 1;
}

void huffman(int n, float P[])
{
    float Lcp = 0;
    int j = 1;
    if (n == 2) {
        C[1][1] = 0;
        Length[1] = 1;
        C[2][1] = 1;
        Length[2] = 1;
    } else {
        q = P[n - 1] + P[n];
        j = Up(n, q);
        huffman(n - 1, P);
        Down(n, j);
    }

}

int main()
{
    setlocale(LC_ALL, "Russian");
    float srLen = 0;
    cout << "Шеннон:" << endl << endl;

    shenon();
    Entropy = 0;

    cout << endl << endl;

    cout << "Гилберт-Мур:" << endl << endl;
    gilbert();
    Entropy = 0;

    cout << endl << endl;

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            C[i][j] = 0;
        }
    }

    cout << "Фано:" << endl << endl;
    fano(1, 10, 0);

    for (int i = 1; i < 11; i++) {
        for (int j = 1; j <= Length[i]; j++) {
            cout << C[i][j];
        }
        cout << " Длина: " << Length[i] << " Вероятность: " << P[i] << endl;
        srLen += Length[i] * P[i];
    }
    cout << endl << "Lcp: " << srLen << endl;
    for (int i = 1; i < n; i++) {
        Entropy -= P[i] * log2(P[i]);
    }
    cout << "Энтропия: " << Entropy << endl << endl;
    Entropy = 0;

    cout << endl << endl;

    cout << "Хаффмен:" << endl << endl;
    srLen = 0;

    huffman(n, P);
    srLen = 0;
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j <= Length[i]; j++) {
            cout << C[i][j];
        }
        cout << " Длина: " << Length[i] << " Вероятность: " << P[i] << endl;
        srLen += Length[i] * P[i];
    }
    cout << endl << "Lcp: " <<  srLen << endl;
    return 0;
}