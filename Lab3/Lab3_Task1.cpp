#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
using namespace std;

// ======== БАЗОВЫЙ КЛАСС ======== //
class Detail {
protected:
    string name;      // Название детали
    string id;        // Идентификатор детали
    double weight;    // Вес детали
    string material;  // Материал детали

    // Конструктор protected, чтобы нельзя было создавать объект напрямую
    Detail(string nm, string ID, double wght, string mtrl)
            : name(nm), id(ID), weight(wght), material(mtrl) {
    }

public:
    // Виртуальный метод вывода информации
    virtual void Display() {
        cout << "=== Деталь ===" << endl;
        cout << "Название детали: " << name << endl;
        cout << "ID детали: " << id << endl;
        cout << "Вес детали: " << weight << " кг" << endl;
        cout << "Материал детали: " << material << endl;
    }

    // Виртуальный деструктор без вывода
    virtual ~Detail() = default;

    // Шаблонная дружественная функция для создания объектов
    template <typename T, typename... Args>
    friend T* CreateObject(vector<Detail*>& storage, Args&&... args);
};

// ======== ПРОИЗВОДНЫЙ КЛАСС ======== //
class Build : public Detail {
protected:
    int numOfParts;     // Количество деталей в сборке
    double buildWeight; // Вес всей сборки
    string buildName;   // Название сборки
    int complexity;     // Сложность сборки

    // Конструктор protected
    Build(string nm, string ID, double wght, string mtrl,
          string bName, double bW, int num, int comp)
            : Detail(nm, ID, wght, mtrl), buildName(bName),
              buildWeight(bW), numOfParts(num), complexity(comp) {
    }

public:
    // Переопределяем метод Display()
    void Display() override {
        cout << "=== Сборка ===" << endl;
        cout << "Название сборки: " << buildName << endl;
        cout << "ID сборки: " << id << endl;
        cout << "Вес сборки: " << buildWeight << " кг" << endl;
        cout << "Материал: " << material << endl;
        cout << "Количество деталей: " << numOfParts << endl;
        cout << "Сложность сборки (1-5): " << complexity << endl;
    }

    // Деструктор без вывода
    ~Build() override = default;

    // Шаблонная дружественная функция для создания объектов
    template <typename T, typename... Args>
    friend T* CreateObject(vector<Detail*>& storage, Args&&... args);
};

// ======== ДРУЖЕСТВЕННАЯ ШАБЛОННАЯ ФУНКЦИЯ ======== //
template <typename T, typename... Args>
T* CreateObject(vector<Detail*>& storage, Args&&... args) {
    T* obj = new T(forward<Args>(args)...); // создаём объект
    storage.push_back(obj);                 // добавляем в хранилище
    return obj;                             // возвращаем указатель
}

// ======== MAIN ======== //
int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8); // вывод в UTF-8
    SetConsoleCP(CP_UTF8);       // ввод в UTF-8

    vector<Detail*> storage; // хранилище указателей на объекты

    // Создаём детали и сборки
    CreateObject<Detail>(storage, "Вал", "D001", 2.5, "Сталь");
    CreateObject<Build>(storage, "Подшипник", "A100", 1.2, "Металл",
                        "Редуктор", 12.5, 6, 4);

    cout << endl << "=== Вывод информации обо всех объектах ===" << endl;

    // Демонстрация полиморфизма: вызываем Display() у разных типов
    for (auto obj : storage) {
        obj->Display();
        cout << endl;
    }

    // Очистка памяти
    for (auto obj : storage) {
        delete obj;
    }
    storage.clear();
    _getch();
    return 0;
}
