#include <iostream>

using namespace std;

struct vertex {
    int Data;
    vertex * Left;
    vertex * Right;
};

void UpToDown (vertex * p) {
    if (p != NULL) {
        cout << p -> Data << ' ';
        UpToDown(p -> Left);
        UpToDown(p -> Right);
    }
}

void LeftToRight (vertex * p) {
    if (p != NULL) {
        LeftToRight(p -> Left);
        cout << p -> Data << ' ';
        LeftToRight(p -> Right);
    }
}

void DownToUp (vertex * p) {
    if (p != NULL) {
        DownToUp(p -> Left);
        DownToUp(p -> Right);
        cout << p -> Data << ' ';
    }
}

vertex* ISDP(int L, int R) {
    vertex * root;
    cout << "Input array size" << endl;
    int x;
    cin >> x;
    int a[x];
    for (int i = 0; i < x; i++) {
        a[i] = i + 1;
    }
    if (L > R) return NULL;
    else {

    }
}

int main() {
    vertex * Root = new vertex;
    vertex * temp = Root;
    Root -> Data = 3;
    Root -> Left = new vertex;
    Root -> Left -> Data = 1;
    Root -> Left -> Left = Root -> Left -> Right = NULL;
    Root -> Right = new vertex;
    Root = Root -> Right;
    Root -> Data = 5;
    Root -> Left = new vertex;
    Root -> Right = NULL;
    Root = Root -> Left;
    Root -> Data = 4;
    Root -> Left = new vertex;
    Root -> Left -> Data = 2;
    Root -> Left -> Left = Root -> Left -> Right = NULL;
    Root -> Right = new vertex;
    Root -> Right -> Data = 6;
    Root -> Right -> Left = Root -> Right -> Right = NULL;
    Root = temp;
    UpToDown(Root);
    cout << endl;
    LeftToRight(Root);
    cout << endl;
    DownToUp(Root);
}
