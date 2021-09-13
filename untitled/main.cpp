#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <clocale>
#include <iostream>

const int nMax = 500;

struct vertex {
    int data;
    vertex *left;
    vertex *right;
};

int a[nMax];
int n;


void FormAscArray()
{
    for (int i = 1; i <= n; i++)
        a[i] = i;
}


vertex *NewNode(int data)
{
    vertex *p = new vertex;
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// ������� ����
vertex *CreateISDP(int l, int r)
{
    if (l > r)
        return NULL;
    int m = (l + r) / 2;
    vertex *p = NewNode(a[m]);
    p->left = CreateISDP(l, m - 1);
    p->right = CreateISDP(m + 1, r);
    return p;
}

int TreeSize(vertex *p)
{
    if (p == NULL)
        return 0;
    return 1 + TreeSize(p->left) + TreeSize(p->right);
}

int Max(int l, int r)
{
    if (l > r)
        return l;
    return r;
}

int TreeHeight(vertex *p)
{
    if (p == NULL)
        return 0;
    return 1 + Max(TreeHeight(p->left), TreeHeight(p->right));
}

long LenSum(vertex *p, int l)
{
    if (p == NULL)
        return 0;
    return l + LenSum(p->left, l + 1) + LenSum(p->right, l + 1);
}

float TreeAverageHeight(vertex *p)
{
    return LenSum(p, 1) * 1.0 / TreeSize(p);
}

long Sum(vertex *p)
{
    if (p == NULL)
        return 0;
    return p->data + Sum(p->left) + Sum(p->right);
}

int IsSearchTree(vertex *p)
{
    if (p != NULL &&
        (
                (p->left != NULL) && ((p->data <= p->left->data) || !IsSearchTree(p->left)) ||
                (p->right != NULL) && ((p->data >= p->right->data) || !IsSearchTree(p->right))
        )
            )
        return 0;
    return 1;
}


int SearchKey(vertex *p, int key)
{
    while (p != NULL) {
        if (key < p->data)
            p = p->left;
        else if (key > p->data)
            p = p->right;
        else
            break;
    }
    if (p != NULL) {
        std::cout << p ;
        return 1;
    }
    return 0;
}

void PrintLeftToRight(vertex *p)
{
    if (p != NULL) {
        PrintLeftToRight(p->left);
        std::cout << p->data << ' ';
        PrintLeftToRight(p->right);
    }
}

void PrintUpToDown (vertex * p) {
    if (p != NULL) {
        std:: cout << p -> data << ' ';
        PrintUpToDown(p->left);
        PrintUpToDown(p->right);
    }
}

void PrintDownToUp (vertex * p) {
    if (p != NULL) {
        PrintDownToUp(p -> left);
        PrintDownToUp(p -> right);
        std::cout << p -> data << ' ';
    }
}

int main()
{
    using namespace std;
    setlocale(LC_ALL, "Russian");
    vertex *root; // ������ ������
    cout << "������� ���������� ������ � ������: " << endl;
    cin >> n;
    FormAscArray();
    root = CreateISDP(1, n); // ������� ������
    cout << "������� ������ ��� ������ ����� �������:" << endl;
    PrintLeftToRight(root);
    cout << endl;
    cout << "������� ������ ��� ������ ������ ����:" << endl;
    PrintUpToDown(root);
    cout << endl;
    cout << "������� ������ ��� ������ ����� �����" << endl;
    PrintDownToUp(root);
    cout << endl;
    printf("��� ������ ������? ");
    if (IsSearchTree(root))
        cout << "��" << endl;
    else
        cout << "���" << endl;
    int key;
    cout << "������� ���� ��� ������ (� ������ ���� ����� �� 1 �� " << n << ')' << endl;
    cin >> key;
    if (SearchKey(root, key))
        cout << "���� ������" << endl;
    else
        cout << "���� �� ������" << endl;
    cout << "������ ������: " << TreeSize(root) << endl;
    cout << "������ ������: " << TreeHeight(root) << endl;
    cout << "������� ������ ������: " << TreeAverageHeight(root) << endl;
    cout << "����������� ����� ������ � �������� ������: " << Sum(root) << endl;

    getch();
}