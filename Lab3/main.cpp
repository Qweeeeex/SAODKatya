#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <clocale>
#include <iostream>
#include <ctime>

const int nMax = 501;

struct vertex {
    int data;
    vertex *left;
    vertex *right;
};

int arr[nMax];
int n;

int random(int x) {
    return rand() % x;
}

void MakeTree(vertex *&root, int D) {
    if (root == NULL) {
        root = new vertex;
        root->data = D;
        root->left = NULL;
        root->right = NULL;
    } else if (root->data < D) {
        MakeTree(root->right, D);
    } else if (root->data > D) {
        MakeTree(root->left, D);
    }
}

int Max(int l, int r) {
    if (l > r)
        return l;
    return r;
}

int Size(vertex *p) {
    if (p == NULL)
        return 0;
    return 1 + Size(p->left) + Size(p->right);
}

int Height(vertex *p) {
    if (p == NULL)
        return 0;
    return 1 + Max(Height(p->left), Height(p->right));
}

long LenSum(vertex *p, int l) {
    if (p == NULL)
        return 0;
    return l + LenSum(p->left, l + 1) + LenSum(p->right, l + 1);
}

float AverageHeight(vertex *p) {
    return LenSum(p, 1) * 1.0 / Size(p);
}

long Sum(vertex *p) {
    if (p == NULL)
        return 0;
    return p->data + Sum(p->left) + Sum(p->right);
}

int IsSearchTree(vertex *p) {
    if (p != NULL &&
        (
                (p->left != NULL) && ((p->data <= p->left->data) || !IsSearchTree(p->left)) ||
                (p->right != NULL) && ((p->data >= p->right->data) || !IsSearchTree(p->right))
        )
            )
        return 0;
    return 1;
}


int Search(vertex *p, int key) {
    while (p != NULL) {
        if (key < p->data)
            p = p->left;
        else if (key > p->data)
            p = p->right;
        else
            break;
    }
    if (p != NULL)
        return 1;
    return 0;
}


void LeftToRight(vertex *p) {
    if (p != NULL) {
        LeftToRight(p->left);
        std::cout << p->data << ' ';
        LeftToRight(p->right);
    }
}

void UpToDown(vertex *p) {
    if (p != NULL) {
        std::cout << p->data << ' ';
        UpToDown(p->left);
        UpToDown(p->right);
    }
}

void DownToUp(vertex *p) {
    if (p != NULL) {
        DownToUp(p->left);
        DownToUp(p->right);
        std::cout << p->data << ' ';
    }
}

void Delete(vertex *&root, int A) {
    vertex **p;
    vertex *q, *s, *r;
    p = &root;

    while (*p != NULL) {
        if ((*p)->data < A) {
            p = &((*p)->right);
        } else if ((*p)->data > A) {
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

int main() {
    using namespace std;
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int Array[10] = {46, 47, 24, 75, 62, 61, 71, 72, 80, 13};
    cout << endl;
    vertex *root;
    root = NULL;

    for (int i = 0; i < 10; i++) {
        MakeTree(root, Array[i]);
    }
    cout << endl << "Вершины дерева при обходе слева направо до удаления:" << endl;
    LeftToRight(root);
    for (int i = 0; i < 10; i++) {
        Delete(root, Array[i]);
        cout << endl << "Вершины дерева при обходе слева направо после удаления " << Array[i] << ':' << endl;
        LeftToRight(root);
        cout << endl;
        cout << endl << "Размер дерева: " << Size(root) << endl;
        cout << endl << "Высота дерева: " << Height(root) << endl;
        cout << endl << "Средняя высота дерева: " << AverageHeight(root) << endl;
        cout << endl << "Контрольная сумма данных в вершинах дерева: " << Sum(root) << endl;
    }
}

