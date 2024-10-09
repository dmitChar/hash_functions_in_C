// 4 основа.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Table {
    string value;
    Table* next;
};

struct Keys {
    Table* data;
};




int CheckSel() {
    int s;
    cin >> s;
    while (cin.fail() || cin.get() != '\n' || s != 1 || s != 2) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cout << "Ошибка ввода! Попробуййте снова: ";
        cin >> s;
    }
    return s;
}

int CheckChoise() {
    int s;
    cin >> s;
    while (cin.fail() || cin.get() != '\n' || s < 1 || s>8) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cout << "Ошибка ввода! Попробуййте снова: ";
        cin >> s;
    }
    return s;
}

string CheckKey() {
    string x;
    cin >> x;
    while (cin.fail() || (cin.get() != '\n') || x[0] < 48 || x[0]>57 || x[1] < 48 || x[1]>57 || x[2] < 65 || x[2]>90 || x[3] < 65 || x[3]>90 || x[4] < 48 || x[4]>57 || x[5] < 48 || x[5]>57) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cout << "Введен ключ некорректного формата! \nПожалуйста, повторите ввод: ";
        cin >> x;
    }
    return x;
}

int HashFunction(string key, int length, int *a) {
    int n = 0;
    for (int i = 0; i < key.size(); i++) {
        n += int(key[i]);
    }
    n = (n-322)*17;
    a[n] += 1;
    return n;
}

string KeyCreate() {
    string key = "";

    for (int j = 0; j < 6; j++) {

        if (j == 0 || j == 1 || j == 4 || j == 5) {
            key += '0' + rand() % ('9' - '0');
        }
        else {
            key += 'A' + rand() % ('Z' - 'A');
        }
    }
    return key;
}

bool IsNew(Keys* k, int a) {
    if (k[a].data == NULL)
        return true;
    else return false;
}

void Add(Keys* k, int a, string val) {
    if (IsNew(k, a)) {

        Table* temp = new Table;
        k[a].data = temp;
        temp->value = val;
        temp->next = NULL;
    }
    else {
        Table* temp = k[a].data;
        while (temp->next != NULL)
            temp = temp->next;
        Table* newtemp = new Table;
        newtemp->value = val;
        newtemp->next = NULL;
        temp->next = newtemp;
    }
}


void Show(Keys* k, int length) {
    for (int i = 0; i < length; i++) {
        cout << i + 1 << ": ";
        Table* temp = k[i].data;
        while (temp != NULL) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;

    }
}

void InFile(Keys* k, int length, string s) {

    ofstream fr;
    fr.open(s);
    for (int i = 0; i < length; i++) {

        fr << i << ": ";
        Table* temp = k[i].data;
        while (temp != NULL) {
            fr << temp->value << " ";
            temp = temp->next;
        }
        fr << endl;

    }
}

bool DelElem(Keys* k, int length, string s) {

    int n;
    bool flag = false; int* h = new int[1500];
    n = HashFunction(s, length, h);

    Table* temp = k[n].data;
    if (temp != NULL) {
        if (temp->value == s) {
            flag = true;
            k[n].data = temp->next;
            delete temp;
        }
        else {
            while (temp->next != NULL) {
                if (temp->next->value == s) {
                    flag = true;
                    break;
                }
                else temp = temp->next;
            }
            if (flag) {
                Table* temp2 = temp->next;
                temp->next = temp2->next;
                delete temp2;
            }
        }
    }
    return flag;

}





int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int length = 1500;
    int* h = new int[1500]{0};
    Keys* k = new Keys[1500];
    int choise = 0; int sel = 0;
    string key = "";
    int a = 0;
    int flag = 0;
    string s; int count = 0;

    while (choise != 9) {

        cout << "Введите 1, чтобы создать пустую хеш-таблицу." << endl;
        cout << "Введите 2, чтобы создать заполненную хеш-таблицу." << endl;
        cout << "Введите 3, чтобы добавить элемент в хеш-таблицу." << endl;
        cout << "Введите 4, чтобы удалить элемент из хеш-таблицы." << endl;
        cout << "Введите 5, чтобы продемонстрировать хеш-таблицу." << endl;
        cout << "Введите 6, чтобы найти элемент в хеш-таблице." << endl;
        cout << "Введите 7, чтобы выгрузить данные хеш-функции." << endl;
        cout << "Введите 8, чтобы завершить работу программы." << endl;
        choise = CheckChoise();
        switch (choise)
        {
        case 1:
            for (int i = 0; i < length; i++) {
                k[i].data = NULL;
            }
            cout << "Хеш таблица успешно создана." << endl;
            flag = 1;
            break;

        case 2:
            for (int i = 0; i < length; i++) {
                k[i].data = 0;
            }
            for (int i = 0; i < length*3; i++) {
                key = KeyCreate();

                a = HashFunction(key, length, h);
                Add(k, a, key);
            }
            flag = 1;
            Show(k, length);
            break;

        case 3:
            cout << "Введите ключ, чтобы добавить элемент в хеш таблицу:"; key = CheckKey();
            a = HashFunction(key, length, h);
            Add(k, a, key);
            cout << "Элемент успешно добавлен!" << endl;
            Show(k, length);
            break;


        case 4:
            if (flag == 0) {
                cout << "Удаление невозможно, сначала заполните хеш таблицу!";
            }
            else cout << "Введите ключ удаляемого элемента:"; key = CheckKey();
            if (DelElem(k, length, key)) {
                cout << "Элемент успешно удален";
                Show(k, length);
            }
            else cout << "Элемент не был найден!" << endl;
            break;

        case 5:
            Show(k, length);

        case 6:
            if (flag == 0) {
                cout << "Невозможно произвести поиск элемента, если не создано ни одного сегмента!" << endl;
            }
            else {
                cout << "Для поиска по ключу нажмите (1), для поиска по номеру нажмите (2): "; sel = CheckSel();

                if (sel == 1) {
                    cout << "Введите ключ: ";
                    key = CheckKey();
                }
            }

        case 7:
            if (flag == 0) {
                cout << "Невозможно произвести выгрузку в файл, если не создано ни одного сегмента!" << endl;
            }
            else {
                s = "J:\\text.txt";
                InFile(k, length, s);
                cout << "Хеш таблица была успешно загружена в файл!";

            }
            break;

        case 8:
            cout << "Программа была успешно закрыта!";
            ofstream hh;
            hh.open("J:\\texst2.txt");
            for (int i = 0; i < length; i++) {
                hh << h[i]<<endl ;
            }
            exit(0);

        }

    }

}

