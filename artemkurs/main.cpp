//---------------------------------------------------------------------------

#pragma hdrstop
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

//---------------------------------------------------------------------------
const int MAX_REC_COUNT = 4000 + 1; // Максимальное количество записей в БД

struct TRecInf { // Запись с информацией
    char fio[30]; // ФИО
    unsigned short department; // Номер отдела
    char position[22]; // Название должности
    char birthDate[10]; // Дата рождения
};

struct TInf { // Структура для формирования очереди
    TRecInf *inf; // Указатель на информацию
    TInf *next; // Указатель на следующий элемент очереди
};

struct TNode { // Структура для узла (вершины) дерева
    TRecInf *inf; // Указатель на информацию
    TNode *left; // Указатель на левую вершину
    TNode *right; // Указатель на правую вершину
    int balance; // Баланс вершины
};

TRecInf *db[MAX_REC_COUNT]; // Индексный массив указателей на записи
int dbRecCount; // Количество записей в индексном массиве db
TInf *qHead; // Указатель на начало очереди
TInf *qTail; // Указатель на конец очереди
int qRecCount; // Количество элементов в очереди


// Проверяет очередь на пустоту.
int IsQueueEmpty()
{
    return qHead == NULL ? 1 : 0;
}

// Устанавливает следующий элемент очереди
void SetQueueNext(TInf *next)
{
    if (IsQueueEmpty())
        qHead = next;
    else
        qTail->next = next;
    qTail = next;
    qTail->next = NULL;
}

// Добавляет элемент inf в очередь
void AddToQueue(TRecInf *inf)
{
    TInf *p = new TInf; // Создаем новый элемент в динамической памяти
    p->inf = inf;
    SetQueueNext(p);
    qRecCount++;
}

// Делает очередь пустой
void EmptyQueue()
{
    qHead = NULL;
    qTail = NULL;
    qRecCount = 0;
}

/* Сравнивает две строки посимвольно.
  Возвращает:
  0, если строки равны,
  -1, если первая строка меньше
  1, если первая строка больше */
int CompareStr(char *s1, char *s2, int len)
{
    int i = 0;
    int m = 0;
    while (i < len && m == 0) {
        if (s1[i] < s2[i])
            m = -1;
        else if (s1[i] > s2[i])
            m = 1;
        i++;
    }
    return m;
}
/* Сравнивает две записи.
  Возвращает:
  0, если записи равны,
  -1, если первая запись меньше
  1, если первая запись больше */
int CompareRec(TRecInf *p1, TRecInf *p2)
{
    int k = CompareStr(p1->fio, p2->fio, 32); // Сравниваем по ФИО
    if (k != 0)
        return k;
    if (p1->department < p2->department) // Сравниваем по номеру отдела
        return -1;
    if (p1->department > p2->department)
        return 1;
    k = CompareStr(p1->position, p2->position, 22); // Сравниваем по должности
    if (k != 0)
        return k;
    int DateSeparator = '-'; // Разделитель в дате
    char s[11];
    s[10] = '\0';
    int i;
    for (i = 0; i < 10; i++)
        s[i] = p1->birthDate[i];
    int TDate d1 = StrToDate(s);
    for (i = 0; i < 10; i++)
        s[i] = p2->birthDate[i];
    int TDate d2 = StrToDate(s);
    if (d1 < d2) // Сравниваем по дате рождения
        return -1;
    if (d1 > d2)
        return 1;
    return 0;
}

// Загружает данные из файла c именем fileName
void Load(char *fileName)
{
    dbRecCount = 0;
    FILE *f = fopen(fileName, "rb"); // Открываем файл для чтения
    while (1) {
        db[dbRecCount] = new TRecInf;
        fread(db[dbRecCount], sizeof(TRecInf), 1, f); // Читаем запись из файла
        if (feof(f))
            break;
        dbRecCount++;
    }
    fclose(f); // Закрываем файл
}

// Переводит число w в строку s длины len с впереди расположенными нулями
void LeadingZeroes(unsigned short w, char *s, int len)
{
    char _s[10];
    itoa(w, _s, 10); // Преобразуем число в строковый вид
    int k = len - strlen(_s);
    s[0] = '\0'; // Очищаем строку, т.е. делаем ее нулевой длины
    for (int i = 0; i < k; i++) // Цикл для добавления нулей впереди
        strcat(s, "0"); // Добавляем 0 впереди
    strcat(s, _s); // Присоединяем к строке само число
}

// Отображает все записи индексного массива db на экране
void BrowseDB()
{
    char s1[10]; // Массив для строкового представления
    int i = 0;
    while (i < dbRecCount) {
        system("cls");
        printf("Количество записей: %d", dbRecCount);
        printf("    Номер первой записи на странице: %d\n\n", i + 1);
        do {
            LeadingZeroes(db[i]->department, s1, 3);
            printf("%.32s отд. %s %.22s род. %.8s",
                   db[i]->fio, s1, db[i]->position, db[i]->birthDate);
            printf("\n");
            i++;
        } while (i % 21 != 0 && i < dbRecCount);
        printf("\nДля продолжения просмотра нажмите клавишу Enter "
               "(Esc - окончание просмотра)");
        if (getch() == 27) // Если нажата клавиша Esc
            return;
    }
}

// Отображает очередь на экране
void BrowseQueue()
{
    TInf *p = qHead;
    char s1[10]; // Массив для строкового представления
    int i = 0;
    while (p != NULL) {
        system("cls");
        printf("Количество записей в очереди: %d", qRecCount);
        printf("    Номер первой записи на странице: %d\n\n", i + 1);
        do {
            i++;
            LeadingZeroes(p->inf->department, s1, 3);
            printf("%.32s отд. %s %.22s род. %.8s",
                   p->inf->fio, s1, p->inf->position, p->inf->birthDate);
            printf("\n");
            p = p->next;
        } while (i % 21 != 0 && p != NULL);
        printf("\nДля продолжения просмотра нажмите клавишу Enter "
               "(Esc - окончание просмотра)");
        if (getch() == 27) // Если нажата клавиша Esc
            return;
    }
}

// Создает новую вершину
TNode *NewNode(TRecInf *d)
{
    TNode *p = new TNode; // Создаем новую вершину и заполняем ее поля
    p->inf = d;
    p->left = NULL;
    p->right = NULL;
    p->balance = 0;
    return p;
}

/* Добавляет вершину в АВЛ-дерево.
  Принимает в качестве параметров:
  d - указатель на запись базы данных,
  p - указатель на вершину,
  growth = 1, если дерево выросло */
TNode *AddNode(TRecInf *d, TNode *p, int& growth)
{
    if (p == NULL) {
        p = NewNode(d); // Если надо формировать новую вершину
        growth = 1;
        return p;
    }
    int k = CompareRec(d, p->inf);
    if (k == 0) {
        puts("Одинаковые записи в базе данных");
        return p;
    }
    TNode *q = NULL;
    TNode *r = NULL;
    if (k < 0) {
        p->left = AddNode(d, p->left, growth); // Движемся к левой вершине текущей вершины
        if (growth == 1)
            switch (p->balance) {
                case 1:
                    p->balance = 0;
                    growth = 0;
                    break;
                case 0:
                    p->balance = -1; // growth останется = 1, чтобы потом возвращаться
                    break;       // в расположенные выше вершины и у них проверять баланс
                case -1:
                    q = p->left;
                    if (q->balance == -1) {
                        q->balance = 0; // LL-поворот
                        p->balance = 0;
                        p->left = q->right;
                        q->right = p;
                        p = q;
                    }
                    else {
                        r = q->right; // LR-поворот
                        if (r->balance == -1)
                            p->balance = 1;
                        else
                            p->balance = 0;
                        if (r->balance == 1)
                            q->balance = -1;
                        else
                            q->balance = 0;
                        r->balance = 0;
                        p->left = r->right;
                        q->right = r->left;
                        r->left = q;
                        r->right = p;
                        p = r;
                    }
                    growth = 0;
                    break;
            }
    }
    else {
        p->right = AddNode(d, p->right, growth); // Движемся к правой вершине текущей вершины
        if (growth == 1)
            switch (p->balance) {
                case -1:
                    p->balance = 0;
                    growth = 0;
                    break;
                case 0:
                    p->balance = 1;
                    break;
                case 1:
                    q = p->right;
                    if (q->balance == 1) {
                        q->balance = 0; // RR-поворот
                        p->balance = 0;
                        p->right = q->left;
                        q->left = p;
                        p = q;
                    }
                    else {
                        r = q->left; // RL-поворот
                        if (r->balance == 1)
                            p->balance = -1;
                        else
                            p->balance = 0;
                        if (r->balance == -1)
                            q->balance = 1;
                        else
                            q->balance = 0;
                        r->balance = 0;
                        p->right = r->left;
                        q->left = r->right;
                        r->left = p;
                        r->right = q;
                        p = r;
                    }
                    growth = 0;
                    break;
            }
    }
    return p;
}

// Создает дерево. Возвращает корень созданного дерева
TNode *CreateTree()
{
    TNode *root = NULL;
    int growth; // = 1, если дерево выросло
    for (int i = 0; i < dbRecCount; i++) {
        growth = 0;
        root = AddNode(db[i], root, growth); // Добавляем вершину в дерево
    }
    return root;
}

// Находит в дереве вершину по ключу. Возвращает указатель на эту вершину
TNode *FindKey(TNode *root, char *key)
{
    TNode *p = root;
    int k;
    while (p != NULL) {
        k = CompareStr(p->inf->fio, key, 3);
        if (k == 0)
            break;
        if (k > 0)
            p = p->left; // Движемся к левой вершине
        else
            p = p->right; // Движемся к правой вершине
    }
    return p;
}

// Создает очередь обходом поддерева слева направо
void CreateQueue(TNode *p, char *key)
{
    if (p == NULL)
        return;
    CreateQueue(p->left, key); // Вызываем рекурсивно для левой вершины
    if (CompareStr(p->inf->fio, key, 3) == 0)
        AddToQueue(p->inf); // Добавляем в очередь
    CreateQueue(p->right, key); // Вызываем рекурсивно для правой вершины
}

#pragma argsused
int main(int argc, char* argv[])
{
    system("cls");
    gotoxy(19, 1);
    printf("Курсовая работа (Древовидные структуры данных)\n\n");
    printf("Для загрузки базы данных нажмите клавишу Enter (Esc - Выход)\n");
    if (getch() == 27) // Если нажата клавиша Esc
        return 0;
    Load("base2.dat");
    BrowseDB(); // Выводим базу данных на экран
    TNode *root = CreateTree(); // Создаем дерево
    system("cls");
    printf("\n");
    printf("Построено дерево поиска, упорядочивающее данные сначала по первому полю, затем  по второму и т.д.\n");
    char key[4]; // Ключ для поиска в дереве
    printf("Введите ключ для поиска в дереве (три буквы, первая буква - заглавная): ");
    scanf("%s", key);
    TNode *p = FindKey(root, key); // Ищем в дереве вершину по ключу
    if (p == NULL) {
        printf("В построенном дереве вершины с таким ключом не найдены.\n");
        printf("Нажмите любую клавишу для выхода\n");
        getch();
        return 0;
    }
    EmptyQueue();
    CreateQueue(p, key); // Создаем очередь из поддерева
    BrowseQueue(); // Отображаем очередь на экране

    return 0;
}