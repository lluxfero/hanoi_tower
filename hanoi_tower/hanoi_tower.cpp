#include <iostream>
#include <Windows.h>
#include <clocale>
using namespace std;

int err_n() {
    int m, ival = 1;
    cin >> m;
    while (ival == 1) {
        if (cin.fail() || m < 1) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Ошибка! Попробуйте еще раз: ";
            cin >> m;
        }
        else
            ival = 0;
    }
    return m;
}

void show_desk(int** D, int n_const) {
    for (int i = 0; i < n_const; i++) {
        for (int j = 0; j < 3; j++)
            cout << D[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

void move_disk(int** D, int n, int x, int y, int n_const) {
    cout << "из стержня " << x << " в стержень " << y  << ":" << endl;

    int p = 0, q = n_const - 1;
    for (int i = 0; i < n_const; i++) {
        if (D[i][x - 1] != 0) {
            p = i;
            break;
        }
    }
    for (int i = 0; i < n_const; i++) {
        if (D[i][y - 1] != 0) {
            q = i - 1;
            break;
        }
    }

    D[q][y - 1] = D[p][x - 1];
    D[p][x - 1] = 0;

    show_desk(D, n_const);
}

void move_tower(int** D, int n, int x, int y, int z, int n_const) {
    if (n == 0) return;
    move_tower(D, n - 1, x, z, y, n_const);
    move_disk(D, n, x, y, n_const);
    move_tower(D, n - 1, z, y, x, n_const);
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int num, k = 1;
    cout << "Введите количество дисков в башне: ";
    num = err_n();

    int** desk = new int* [num];
    for (int i = 0; i < num; i++)
        desk[i] = new int[3];
    for (int i = 0; i < num; i++)
        for (int j = 0; j < 3; j++)
            desk[i][j] = 0;

    for (int i = 0; i < num; i++) {
        desk[i][0] = k;
        k++;
    }

    show_desk(desk, num);

    move_tower(desk, num, 1, 2, 3, num);
}
