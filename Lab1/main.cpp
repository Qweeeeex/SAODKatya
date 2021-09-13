#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

typedef struct mt {
    struct mt* next;
    int x = 0;
} a;

int size = 0;

mt* FillIncStack(void) {
    mt* l, *k = 0;
    l = NULL;
    for (int i = size; i > 0; i--) {
        k = new mt;
        k -> next = l;
        l = k;
        k -> x = i;
    }
    return k;
}

mt * FillDecStack(void) {
    mt *l, *k = 0;
    l = NULL;
    for (int i = 1; i <= size; i++) {
        k = new mt;
        k -> next = l;
        l = k;
        k -> x = i;
    }
    return k;
}

mt* FillRandStack(void) {
    mt *l, *k = 0;
    l = NULL;
    for (int i = 1; i <= size; i++) {
        k = new mt;
        k -> next = l;
        l = k;
        k -> x= rand() % 10;
    }
    return k;
}

mt* FillIncQueue(void) {
    mt* l, * k = 0;
    l = NULL;
    for (int i = size; i > 0; i--) {
        k = new mt;
        k -> x = i;
        k -> next = l;
        l = k;
    }
    return k;
}

mt *FillDecQueue(void) {

    mt *l, *k = 0;
    l = NULL;
    for (int i = 1; i <= size; i++) {
        k = new mt;
        k -> x = i;
        k -> next = l;
        l = k;
    }
    return k;
}

mt *FillRandQueue(void) {
    mt *l, *k = 0;
    l = NULL;
    for (int i = 1; i <= size; i++) {
        k = new mt;
        k->x = rand() % 10;
        k->next = l;
        l = k;
    }
    return k;
}

void Clean(mt *head) {
    mt *l, *k;
    k = l = head;
    while (l != NULL) {
        l = k->next;
        delete k;
        k = l;
    }
    head = NULL;
}

void print(mt *head) {
    mt *l = head;
    while (l != NULL) {
        cout << l->x << " ";
        l = l->next;
    }
}

int CheckAmount(mt *head) {
    mt *l = head;
    int amount = 0;
    while (l != NULL) {
        amount = amount + l->x;
        l = l->next;
    }
    return amount;
}

int CheckSeries(mt *head) {
    mt *k = 0, *l = head;
    int series = 1;
    k = l->next;
    while (k->next != NULL) {
        k = l->next;
        if (l->x > k->x) {
            series = series + 1;
        }
        l = l->next;
    }

    return series;
}

void sort(mt *head) {
    mt* a = head, * b = head->next;
    mt* help = NULL;
    mt* help2 = new mt;
    int min;
    while (a->next != NULL) {
        min = a->x;
        while (b != NULL) {
            if (b->x < min) {
                min = b->x;
                help = b;
            }
            b = b->next;
        }

        if (a->x != min) {
            help2->x = a->x;
            a->x = min;
            help->x = help2->x;
        }
        a = a->next;
        b = a->next;
    }
}

int main() {
    mt *s;
    cout << "Input size of queue:";
    cin >> size;
    cout << endl << "Dec:" << endl;
    s = FillDecQueue();
    print(s);
    sort(s);
    cout << endl;
    print(s);
    cout << endl;
}