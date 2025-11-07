#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

template <typename T>
class Storage {
private:
    const size_t MAX_SIZE = 10; // Максимальное количество элементов (для демонстрации length_error)
public:
    vector<T*> storage; // Вектор указателей на объекты типа T
    // Метод добавления объекта в контейнер
    void add(T* object) {
        if (storage.size() >= MAX_SIZE) {
            // При превышении допустимого размера выбрасывается исключение length_error
            throw length_error("Ошибка! Превышен допустимый размер хранилища.");
        }
        storage.push_back(object);
    }

    // Перегруженный оператор [] с проверкой диапазона
    T* operator[](size_t index) {
        if (index >= storage.size()) {
            // Если индекс выходит за границы — выбрасываем исключение out_of_range
            throw out_of_range("Ошибка! Индекс за пределами диапазона!");
        }
        return storage[index];
    }

    // Метод для получения текущего размера контейнера
    size_t Size() {
        return storage.size();
    }

    // Деструктор — освобождает динамически выделенную память
    ~Storage() {
        for (auto obj : storage)
            delete obj; // Удаляем каждый объект, чтобы не было утечек памяти
    }
};

class Transport {
public:
    string name;     // Название транспорта
    float speed;     // Скорость (км/ч)
    int capacity;    // Вместимость (кол-во человек)

    // Виртуальный метод для вывода информации
    virtual void ShowInfo() {
        cout << "Название транспорта: " << name << "\nСкорость: " << speed << " км/ч" << "\nВместимость: " << capacity << " чел." << endl;
    }

    // Виртуальный деструктор (чтобы правильно удалялись объекты наследников)
    virtual ~Transport() = default;
};

class Bicycle : public Transport {
public:
    Bicycle(const string& n, float s, int c) {
        name = n;
        speed = s;
        capacity = c;
    }

    void ShowInfo() override {
        cout << "Название модели велосипеда: " << name << "\nСкорость: " << speed << " км/ч" << "\nВместимость: " << capacity << " чел." << endl;
    }
};

class Car : public Transport {
public:
    Car(const string& n, float s, int c, const string& engine, int d, const string& body) {
        name = n;
        speed = s;
        capacity = c;
        engineType = engine;
        doors = d;
        bodyType = body;
    }

    string engineType; // Тип двигателя
    int doors; // Кол-во дверей
    string bodyType; // Тип кузова

    void ShowInfo() override {
        cout << "Название модели автомобиля: " << name << "\nСкорость: " << speed << " км/ч" << "\nВместимость: " << capacity << " чел." << "\nТип двигателя: " << engineType << "\nКол-во дверей: " << doors << "\nТип кузова: " << bodyType << endl;
    }
};

class Truck : public Transport {
public:
    Truck(const string& n, float s, int c, double lc, int ax) {
        name = n;
        speed = s;
        capacity = c;
        loadCapacity = lc;
        axles = ax;
    }

    double loadCapacity; // Грузоподъёмность
    int axles; // Кол-во осей

    void ShowInfo() override {
        cout << "Название модели грузовика: " << name << "\nСкорость: " << speed << " км/ч" << "\nВместимость: " << capacity << " чел." << "\nГрузоподъёмность: " << loadCapacity << " т." << "\nКол-во осей: " << axles << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    Storage<Transport> transportStorage;

    transportStorage.add(new Bicycle{ "Stels", 25.0f, 1 });
    transportStorage.add(new Car{ "BMW X5", 220.0f, 5, "бензиновый", 5, "внедорожник" });
    transportStorage.add(new Truck{ "Volvo FH16", 120.0f, 2, 25.0, 4 });

    for (size_t i = 0; i < transportStorage.Size(); ++i) {
        transportStorage[i]->ShowInfo();
        cout << "----------------------\n";
    }

    // Проверка исключения out_of_range
    cout << "\nПроверка выхода за границы:\n";
    try {
        transportStorage[10]->ShowInfo();
    }
    catch (const out_of_range& e) {
        cout << e.what() << endl;
    }

    // Проверка переполнения контейнера
    cout << "\nПроверка переполнения контейнера:\n";
    try {
        for (int i = 0; i < 15; ++i)
            transportStorage.add(new Bicycle("TestBike", 20.0f, 1));
    }
    catch (const length_error& e) {
        cout << e.what() << endl;
    }

    // Проверка утечек памяти
    _CrtDumpMemoryLeaks();
    _getch();
}
