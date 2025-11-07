#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h> // Для установки кодировки консоли
using namespace std;

// ======== БАЗОВЫЙ КЛАСС ======== //
class Base {
protected:
    string name; // Имя объекта
    int value;   // Значение объекта

    // Конструктор protected, чтобы нельзя было создавать объект напрямую вне шаблонной функции
    Base(const string& nm, int val) : name(nm), value(val) {}

public:
    // Виртуальный метод для отображения информации о объекте
    virtual void Display() const {
        cout << "=== Base ===\nИмя: " << name << ", Значение: " << value << endl;
    }

    // Виртуальный метод Clone для полиморфного копирования объектов
    virtual Base* Clone() const {
        return new Base(*this); // Возвращаем копию базового объекта
    }

    virtual ~Base() = default; // Виртуальный деструктор (не выводим информацию)

    // Шаблонная дружественная функция для создания объектов
    template <typename T, typename... Args>
    friend T* CreateObject(vector<Base*>& storage, Args&&... args);
};

// ======== ПРОИЗВОДНЫЙ КЛАСС ======== //
class Derived : public Base {
protected:
    double extra; // Дополнительное поле для Derived

    // Конструктор protected
    Derived(const string& nm, int val, double ext) : Base(nm, val), extra(ext) {}

public:
    // Переопределяем Display для Derived, показываем дополнительное поле
    void Display() const override {
        cout << "=== Derived ===\nИмя: " << name
             << ", Значение: " << value
             << ", Дополнительно: " << extra << endl;
    }

    // Переопределяем Clone для корректного копирования Derived
    Base* Clone() const override {
        return new Derived(*this);
    }

    ~Derived() override = default; // Деструктор без вывода

    // Дружественная функция для создания объектов
    template <typename T, typename... Args>
    friend T* CreateObject(vector<Base*>& storage, Args&&... args);
};

// ======== ШАБЛОННАЯ ФУНКЦИЯ СОЗДАНИЯ ОБЪЕКТОВ ======== //
// Создает объект любого типа (Base или Derived), возвращает указатель на него
template <typename T, typename... Args>
T* CreateObject(vector<Base*>& storage, Args&&... args) {
    T* obj = new T(forward<Args>(args)...); // Создаем объект с переданными аргументами
    return obj; // Возвращаем указатель (копия будет добавлена через add)
}

// ======== ФУНКЦИЯ add ======== //
// Добавляет копию объекта в общее хранилище
void add(vector<Base*>& storage, Base* obj) {
    storage.push_back(obj->Clone()); // Клонируем объект и сохраняем в storage
}

// ======== MAIN ======== //
int main() {
    // Настройка консоли для корректного вывода русских символов
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    srand((time(NULL))); // Инициализация генератора случайных чисел

    vector<Base*> storage; // Общее хранилище объектов

    // ===== Создание случайных объектов =====
    for (int i = 0; i < 6; ++i) {
        if (rand() % 2 == 0) { // Чётное -> Base
            Base* b = CreateObject<Base>(storage, "BaseObj" + to_string(i), i * 10);
            add(storage, b);    // Добавляем копию в хранилище
            delete b;           // Оригинал не нужен
        }
        else {               // Нечётное -> Derived
            Derived* d = CreateObject<Derived>(storage, "DerivedObj" + to_string(i), i * 10, i * 1.5);
            add(storage, d);    // Добавляем копию в хранилище
            delete d;           // Оригинал удаляем
        }
    }

    // ===== Демонстрация полиморфизма =====
    cout << "\n=== Содержимое хранилища ===" << endl;
    for (const auto& obj : storage) {
        obj->Display(); // Вызов виртуального метода показывает правильный тип
        cout << endl;
    }

    // ===== Освобождение ресурсов =====
    for (auto obj : storage) {
        delete obj; // Удаляем все объекты из хранилища
    }
    storage.clear();
    _getch();
    return 0;
}
