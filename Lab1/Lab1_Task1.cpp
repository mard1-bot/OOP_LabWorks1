#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "Пункт А (динамический массив int):\n";
    int n;
    cin >> n;

    // Динамическое выделение массива
    int* mass = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> mass[i];
    }

    // Вывод массива
    cout << "Элементы массива: ";
    for (int i = 0; i < n; i++) {
        cout << mass[i] << " ";
    }

    // Адреса и смещения
    cout << "\nАдрес начала массива: " << &mass[0] << '\n';
    cout << "Смещения (в байтах): ";
    for (int i = 0; i < n; i++) {
        cout << i * sizeof(int) << " ";
    }
    cout << "\n";

    cout << "\nПункт Б (статический массив double[10]):\n";
    double mass1[10];
    for (int i = 0; i < 10; i++) {
        cin >> mass1[i];
    }

    cout << "Элементы массива: ";
    for (int i = 0; i < 10; i++) {
        cout << mass1[i] << " ";
    }

    cout << "\nАдрес начала массива: " << &mass1[0] << '\n';
    cout << "Смещения (в байтах): ";
    for (int i = 0; i < 10; i++) {
        cout << i * sizeof(double) << " ";
    }
    cout << "\n";

    cout << "\nПункт В (статический массив short[10]):\n";
    short mass2[10];
    for (int i = 0; i < 10; i++) {
        cin >> mass2[i];
    }

    cout << "Элементы массива: ";
    for (int i = 0; i < 10; i++) {
        cout << mass2[i] << " ";
    }

    cout << "\nАдрес начала массива: " << &mass2[0] << '\n';
    cout << "Смещения (в байтах): ";
    for (int i = 0; i < 10; i++) {
        cout << i * sizeof(short) << " ";
    }
    cout << "\n";

    // Освобождение динамической памяти
    delete[] mass;
}

