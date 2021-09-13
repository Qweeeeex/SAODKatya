#include <iostream>
#include <cmath>
#include <clocale>
#include <Windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

struct Vertex {
    int data;
    Vertex *left;
    Vertex *right;
    int Balance;
    int weight;
    int use;
} Root;
bool rost = true;
int ym = 1, VR = 1, HR = 1;
Vertex *q = new Vertex;

void SDPr(Vertex *&root, int D);

void SDP(Vertex *&root, int A, int B);

void obhod(Vertex *root);

int treeSize(Vertex *root);

float treeHeight(Vertex *root);

int treeSum(Vertex *root);

float SrH(Vertex *root, int L);

void Delete(Vertex *&root, int x);

Vertex *search(Vertex *root, int key);

void AddAVL(Vertex *&root, int D);

void LL(Vertex *&p);

void RR(Vertex *&p);

void LR(Vertex *&p);

void RL(Vertex *&p);

void BL(Vertex *&p);

void BR(Vertex *&p);

void LL1(Vertex *&p);

void RR1(Vertex *&p);

void DEL(Vertex *&r);

void DeleteAVL(Vertex *&p, int x);

void B2Insert(Vertex *&p, int D);

void bubbleSort(Vertex arr[], int N);

void Midle(Vertex arr[], int N, Vertex *&root);

int Lvl(int X, Vertex *&root);

void CT(int L, int R, int **AR, Vertex *&root, Vertex arr[]);

void ShowMatrix(int **&M, int N);

void FillARAP(int **AW, int **AR, int **AP, int N);

void FillAW(int **&AW, Vertex arr[], int N);

void NullDiag(int **&AW, int **&AR, int **&AP, int N);

void A2(Vertex *&root, int L, int R, Vertex A[]);

void A1(Vertex *&root, Vertex arr[]);

float treeSrWeight(Vertex *&root, int A);

float treeWeight(Vertex *&root);

void bubbleSortSr(Vertex arr[], int N);
void ShowMatrixAW(int **&M, int N) {
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N; j++)
            cout << M[i][j] << ' ';
        cout << endl;
    }
}

int main() {
    //srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    Vertex *root = NULL;
    Vertex *root1 = NULL;
    Vertex *root2 = NULL;
    const int N = 10;
    Vertex arr[N];
    Vertex arr2[N];
    int **AW = new int *[N+1];
    int **AP = new int *[N];
    int **AR = new int *[N];
    AW[0] = new int[N+1];
    for (int i = 0; i < N; i++) {
        AW[i+1] = new int[N+1];
        AP[i] = new int[N];
        AR[i] = new int[N];
    }

    for (int i = 0; i < N; i++) {
        arr2[i].data = arr[i].data = i + 1;
        cout << i + 1 << " Data: " << arr[i].data;
        arr2[i].weight = arr[i].weight = rand() % 10 + 2;
        cout << " Weight: " << arr[i].weight << endl;
    }
    bubbleSortSr(arr, N);
    /*cout << endl << "A1 :" << endl;
    A1(root, arr);
    obhod(root);
    cout << endl << "Vzveshannaya visota: " << treeSrWeight(root, 1);
    cout << endl << "Obschiy ves dereva: " << treeWeight(root);
    cout << endl << "Srednevzveshannaya visota:  " << treeSrWeight(root, 1) / treeWeight(root);
    cout << endl << endl << "A2 :" << endl;
    A2(root1, 0, N - 1, arr);
    obhod(root1);
    cout << endl;
    cout << endl << "Vzveshannaya visota: " << treeSrWeight(root1, 1);
    cout << endl << "Obschiy ves dereva: " << treeWeight(root1);
    cout << endl << "Srednevzveshannaya visota:  " << treeSrWeight(root1, 1) / treeWeight(root1);
    bubbleSort(arr2, N);*/
    NullDiag(AW, AR, AP, N);
    FillAW(AW, arr2, N+1);
    FillARAP(AW, AR, AP, N);
    cout << endl << "Matrix AW: " << endl;
    ShowMatrixAW(AW, N+1);
    cout << endl << "Matrix AP: " << endl;
    ShowMatrix(AP, N);
    cout << endl << "Matrix AR: " << endl;
    ShowMatrix(AR, N);
    cout << endl << endl;
    CT(0, N - 1, AR, root2, arr);
    cout << endl << endl << "DOP :" << endl;
    obhod(root2);
    cout << endl << endl;
    for (int i = 0; i < N - 1; i++) {
        cout << arr2[i].data << " on level " << Lvl(arr2[i].data, root2) << endl;
    }

   // Midle(arr, N, root2);

    cout << endl << "vzveshannaya visota: " << treeSrWeight(root2, 1);
    cout << endl << "obschiy ves dereva: " << treeWeight(root2);
    cout << endl << "Srednevzveshannaya visota:  " << treeSrWeight(root2, 1) / treeWeight(root2);
    cout << endl << std::fixed << std::setprecision(3) << (float)AP[0][N - 1] / (float)AW[0][N - 1] << " ";
    return 0;
}

void A1(Vertex *&root, Vertex arr[]) {
    int index;
    int max = -1;
    for (int i = 0; i < 10; i++) {
        arr[i].use = 0;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if ((arr[j].weight > max) && (arr[j].use == 0)) {
                max = arr[j].weight;
                index = j;
            }
        }
        arr[index].use = 1;
        SDP(root, arr[index].data, arr[index].weight);
        max = -1;
    }
}

void A2(Vertex *&root, int L, int R, Vertex A[]) {
    int i = 0;
    float wes = 0, sum = 0;
    if (L <= R) {
        for (i = L; i <= R; i++) {
            wes += A[i].weight;
        }
        for (i = L; i < R; i++) {
            if ((sum < wes / 2) && (sum + A[i].weight >= wes / 2)) {
                break;
            }
            sum += A[i].weight;
        }
        SDP(root, A[i].data, A[i].weight);
        A2(root, L, i - 1, A);
        A2(root, i + 1, R, A);
    }
}

void B2Insert(Vertex *&p, int D) {
    if (p == NULL) {
        p = new Vertex;
        p->data = D;
        p->left = NULL;
        p->right = NULL;
        p->Balance = 0;
        VR = 1;
    } else if (p->data > D) {
        B2Insert(p->left, D);
        if (VR == 1) {
            if (p->Balance == 0) {
                q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->Balance = 1;
                VR = 0;
                HR = 1;
            } else {
                p->Balance = 0;
                VR = 1;
                HR = 0;
            }
        } else {
            HR = 0;
        }
    } else if (p->data < D) {
        B2Insert(p->right, D);
        if (VR == 1) {
            p->Balance = 1;
            HR = 1;
            VR = 0;
        } else if (HR == 1) {
            if (p->Balance == 1) {
                q = p->right;
                p->Balance = 0;
                q->Balance = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            } else {
                HR = 0;
            }
        }
    }
}

void BL(Vertex *&p) {
    if (p->Balance == -1) {
        p->Balance = 0;
    } else if (p->Balance == 0) {
        p->Balance = 1;
        ym = 0;
    } else if (p->Balance == 1) {
        if (p->right->Balance >= 0) {
            RR1(p);
        } else {
            RL(p);
        }
    }
}

void BR(Vertex *&p) {
    if (p->Balance == 1) {
        p->Balance = 0;
    } else if (p->Balance == 0) {
        p->Balance = -1;
        ym = 0;
    } else if (p->Balance == -1) {
        if (p->left->Balance <= 0) {
            LL1(p);
        } else {
            LR(p);
        }
    }
}

void LL1(Vertex *&p) {
    Vertex *q;
    q = p->left;
    if (q->Balance == 0) {
        q->Balance = 1;
        p->Balance = -1;
        ym = 0;
    } else {
        q->Balance = 0;
        p->Balance = 0;
    }
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR1(Vertex *&p) {
    Vertex *q;
    q = p->right;
    if (q->Balance == 0) {
        q->Balance = -1;
        p->Balance = 1;
        ym = 0;
    } else {
        q->Balance = 0;
        p->Balance = 0;
    }
    p->right = q->left;
    q->left = p;
    p = q;
}

void DEL(Vertex *&r) {
    if (r->right != NULL) {
        DEL(r->right);
        if (ym == 1) {
            BR(r);
        }
    } else {
        q->data = r->data;
        q = r;
        r = r->left;
        ym = 1;
    }
}

void DeleteAVL(Vertex *&p, int x) {
    if (p == NULL) {
        cout << "not found";
    } else if (x < p->data) {
        DeleteAVL(p->left, x);
        if (ym == 1) {
            BL(p);
        }
    } else if (x > p->data) {
        DeleteAVL(p->right, x);
        if (ym == 1) {
            BR(p);
        }
    } else {
        q = p;
        if (q->left == NULL) {
            p = q->right;
            ym = 1;
        } else if (q->right == NULL) {
            p = q->left;
            ym = 1;
        } else {
            DEL(q->left);
            if (ym == 1) {
                BL(p);
            }
        }
        free(q);
    }
}

void LL(Vertex *&p) {
    Vertex *q;
    q = p->left;
    p->Balance = 0;
    q->Balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR(Vertex *&p) {
    Vertex *q;
    q = p->right;
    p->Balance = 0;
    q->Balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void LR(Vertex *&p) {
    Vertex *q = p->left;
    Vertex *r = q->right;
    if (r->Balance < 0) {
        p->Balance = 1;
    } else {
        p->Balance = 0;
    }
    if (r->Balance > 0) {
        q->Balance = -1;
    } else {
        q->Balance = 0;
    }
    r->Balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void RL(Vertex *&p) {
    Vertex *q = p->right;
    Vertex *r = q->left;
    if (r->Balance > 0) {
        p->Balance = -1;
    } else {
        p->Balance = 0;
    }
    if (r->Balance < 0) {
        q->Balance = 1;
    } else {
        q->Balance = 0;
    }
    r->Balance = 0;
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
}

void AddAVL(Vertex *&root, int D) {
    if (root == NULL) {
        root = new Vertex;
        root->data = D;
        root->left = NULL;
        root->right = NULL;
        root->Balance = 0;

        rost = true;
    } else if (root->data > D) {
        AddAVL(root->left, D);

        if (rost == true) {
            if (root->Balance > 0) {
                root->Balance = 0;
                rost = false;
            } else if (root->Balance == 0) {
                root->Balance = -1;
                rost = true;
            } else {
                if (root->left->Balance < 0) {
                    LL(root);
                    rost = false;
                } else {
                    LR(root);
                    rost = false;
                }
            }
        }
    } else if (root->data < D) {
        AddAVL(root->right, D);

        if (rost == true) {
            if (root->Balance < 0) {
                root->Balance = 0;
                rost = false;
            } else if (root->Balance == 0) {
                root->Balance = 1;
                rost = true;
            } else {
                if (root->right->Balance > 0) {
                    RR(root);
                    rost = false;
                } else {
                    RL(root);
                    rost = false;
                }
            }
        }
    }
}

void Delete(Vertex *&root, int x) {
    Vertex **p;
    Vertex *q, *s, *r;
    p = &root;

    while (*p != NULL) {
        if ((*p)->data < x) {
            p = &((*p)->right);
        } else if ((*p)->data > x) {
            p = &((*p)->left);
        } else {
            break;
        }
    }

    if (*p != NULL) {
        q = *p;
        if (q->left == NULL) {
            *p = q->right;
        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            r = q->left;
            s = q;
            if (r->right == NULL) {
                r->right = q->right;
                *p = r;
            } else {
                while (r->right != NULL) {
                    s = r;
                    r = r->right;
                }
                s->right = r->left;
                r->left = q->left;
                r->right = q->right;
                *p = r;
            }
        }
        delete (q);
    }
}

void SDP(Vertex *&root, int A, int B) {
    Vertex **p;

    p = &root;
    while (*p != NULL) {
        if (A < (*p)->data) {
            p = &((*p)->left);
        } else if (A >= (*p)->data) {
            p = &((*p)->right);
        } else {
            break;
        }
    }
    if (*p == NULL) {
        *p = new Vertex;
        (*p)->data = A;
        (*p)->weight = B;
        (*p)->left = NULL;
        (*p)->right = NULL;
    }
}

void SDPr(Vertex *&root, int D) {
    if (root == NULL) {
        root = new Vertex;
        root->data = D;

        root->left = NULL;
        root->right = NULL;
    } else if (root->data < D) {
        SDPr(root->right, D);
    } else if (root->data > D) {
        SDPr(root->left, D);
    }
}

void obhod(Vertex *root) {
    if (root != NULL) {
        obhod(root->left);
        cout << root->data << " ";
        obhod(root->right);
    }
}

int treeSize(Vertex *root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + treeSize(root->left) + treeSize(root->right);
    }
}

float treeSrWeight(Vertex *&root, int A) {
    if (root == NULL) {
        return 0;
    } else {
        return root->weight * A + treeSrWeight(root->left, A + 1) + treeSrWeight(root->right, A + 1);
    }
}

float treeWeight(Vertex *&root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->weight + treeWeight(root->left) + treeWeight(root->right);
    }
}

float treeHeight(Vertex *root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + max(treeHeight(root->left), treeHeight(root->right));
    }
}

int treeSum(Vertex *root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->data + treeSum(root->left) + treeSum(root->right);
    }
}

float SrH(Vertex *root, int L) {
    if (root == NULL) {
        return 0;
    } else {
        return L + SrH(root->left, L + 1) + SrH(root->right, L + 1);
    }
}

Vertex *search(Vertex *root, int key) {
    while (root != NULL) {
        if (root->data < key) {
            root = root->right;
        } else if (root->data > key) {
            root = root->left;
        } else {
            root->data = key;
            break;
        }
    }

    if (root != NULL) {
        cout << "??????? ???????" << endl;
        cout << "???????? ???????: " << root->data << endl;
    } else {
        cout << "??????? ?? ???????" << endl;
    }
    return root;
}

void NullDiag(int **&AW, int **&AR, int **&AP, int N) {
    for (int j = 0; j < N; j++) {
        for (int i = j; i < N; i++) {
            AW[i][j] = 0;
            AR[i][j] = 0;
            AP[i][j] = 0;
        }
    }
}

void FillAW(int **&AW, Vertex arr[], int N) {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            AW[i][j] = AW[i][j - 1] + arr[j - 1].weight;
}

void FillARAP(int **AW, int **AR, int **AP, int N) {
    int j = 0, m = 0, min = 0, x = 0;
    for (int i = 0; i < N; i++) {
        j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h <= N; h++) {
        for (int i = 0; i < N - h; i++) {
            j = i + h;
            m = AR[i][j - 1];
            min = AP[i][m - 1] + AP[m][j];
            for (int k = m + 1; k <= AR[i + 1][j]; k++) {
                x = AP[i][k - 1] + AP[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void ShowMatrix(int **&M, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << M[i][j] << ' ';
        cout << endl;
    }
}


void CT(int L, int R, int **AR, Vertex *&root, Vertex arr[]) {
    if (L < R) {
        int k = AR[L][R];
        SDP(root, arr[k].data, arr[k].weight);
        CT(L, k - 1, AR, root, arr);
        CT(k, R, AR, root, arr);
    }
}

int Lvl(int X, Vertex *&root) {
    if (X < root->data) {
        return 1 + Lvl(X, root->left);
    } else if (X > root->data) {
        return 1 + Lvl(X, root->right);
    } else {
        return 1;
    }
}

void Midle(Vertex arr[], int N, Vertex *&root) {
    int W = 0, S = 0;
    for (int i = 0; i < N ; i++)
        W += arr[i].weight;
    cout << "Obschiy ves: " << W << " " << endl;
    for (int i = 0; i < N - 1; i++)
        S += arr[i].weight * Lvl(arr[i].data, root);
    cout << "Ves po urovnyam: " << S << " " << endl;
    cout << "Srednevzveshannaya visota: " << std::fixed << std::setprecision(3) << (float) S / (float) W << " ";
}

void bubbleSort(Vertex arr[], int N) {
    int i, j;
    bool swapped;
    for (i = 0; i < N; i++) {
        swapped = false;
        for (j = 0; j < N - 1; j++) {
            if (arr[j].data > arr[j + 1].data) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void bubbleSortSr(Vertex arr[], int N) {
    int i, j;
    bool swapped;
    for (i = 0; i < N; i++) {
        swapped = false;
        for (j = 0; j < N - 1; j++) {
            if (arr[j].weight > arr[j + 1].weight) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}