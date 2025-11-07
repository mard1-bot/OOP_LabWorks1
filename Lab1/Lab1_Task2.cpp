#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

/// Функция перевода типа книги в строку
string TypeToString(int tp) {
    switch (tp) {
        case 1:
            return "Художественная";
        case 2:
            return "Техническая";
        default:
            throw "Неправильный тип книги!";
    }
}

/// Класс "Книга"
class Book {
private:
    string author;     // Автор
    string book_name;  // Название
    int type;          // Тип книги (1 — художественная, 2 — техническая)
public:
    Book(const string& name, const string& title, const int& tp)
            : author(name), book_name(title), type(tp)
    {
        if (author.empty() || title.empty()) {
            throw "Ошибка! Отсутствует автор или название книги!";
        }
        if (tp != 1 && tp != 2) {
            throw "Неправильный тип книги!";
        }
    }
    string getBook() const {
        return "Автор: " + author + " | Название: " + book_name + " | Тип: " + TypeToString(type);
    }
    int getType() const { return type; }
};

/// Подсчёт количества книг с использованием switch
void CountWithSwitch(const vector<Book>& Books) {
    int artist = 0;
    int technical = 0;
    for (const auto& book : Books) {
        switch (book.getType()) {
            case 1:
                artist += 1;
                break;
            case 2:
                technical += 1;
                break;
        }
    }

    cout << "\nСтатистика (через switch):\n";
    cout << "  Художественная литература: " << artist << endl;
    cout << "  Техническая литература:    " << technical << endl;
}

/// Подсчёт количества книг без switch
void CountWithoutSwitch(const vector<Book>& Books) {
    int artist = 0;
    int technical = 0;
    for (const auto& book : Books) {
        if (book.getType() == 1)
            artist += 1;
        else
            technical += 1;
    }

    cout << "\nСтатистика (через if/else):\n";
    cout << "  Художественная литература: " << artist << endl;
    cout << "  Техническая литература:    " << technical << endl;
}

int main() {
    // Устанавливаем поддержку кириллицы (Windows-1251)
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int nmbr_of_bks;
    cout << "Введите количество книг: ";
    cin >> nmbr_of_bks;

    vector<Book> Books;
    cin.ignore(); // чтобы корректно работал первый getline

    // Ввод книг
    for (int i = 0; i < nmbr_of_bks; i++) {
        string author, title;
        int type;

        cout << "\nКнига " << i + 1 << ":\n";
        cout << "  Автор: ";
        getline(cin, author);

        cout << "  Название: ";
        getline(cin, title);

        cout << "  Тип (1 - Художественная, 2 - Техническая): ";
        cin >> type;
        cin.ignore(); // очищаем буфер после числа

        Books.push_back(Book(author, title, type));
    }

    // Вывод списка книг
    cout << "\nСписок книг:\n";
    for (size_t i = 0; i < Books.size(); i++) {
        cout << "  " << i + 1 << ". " << Books[i].getBook() << endl;
    }

    // Статистика
    CountWithSwitch(Books);
    CountWithoutSwitch(Books);

    cout << "\nПрограмма завершена.\n";
    return 0;
}
