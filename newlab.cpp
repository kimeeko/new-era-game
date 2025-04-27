#include "Header.h"
using namespace std;
using namespace Nastolki;

int main() {
    setlocale(LC_ALL, "Rus");
    List list;
    list.load("igri1");

    int choice;
    string vid;
    int min_price;

    do {
        cout << "Меню:" << endl;
        cout << "1. Показать все товары" << endl;
        cout << "2. Добавить новый товар" << endl;
        cout << "3. Удалить товар по индексу" << endl;
        cout << "4. Найти по типу и цене" << endl;
        cout << "5. Редактировать товар по индексу" << endl;
        cout << "6. Выход" << endl;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            list.print();
            break;
        case 2: {
            string name, sloznost, vid;
            int vozrast, chislo_people, price;
            cout << "Введите Имя, Тип, Минимальный возраст игрока, Сложность, Количество игроков, Цену товара: ";
            cin >> name >> vid >> vozrast >> sloznost >> chislo_people >> price;
            list.push(name, vid, vozrast, sloznost, chislo_people, price);
            list.save("igri1");
            break;
        }
        case 3:
            list.print();
            if (list.size() > 0) {
                int index;
                cout << "Введите индекс товара для удаления: ";
                cin >> index;
                list.remove(index);
                list.save("igri1");
            }
            break;
        case 4:
            cout << "Введите тип и минимальную цену товара: ";
            cin >> vid >> min_price;
            list.search(vid, min_price);
            break;
        case 5:
            list.print();
            if (list.size() > 0) {
                int index;
                cout << "Введите индекс товара для редактирования: ";
                cin >> index;
                list.edit(index);
                list.save("igri1");
            }
            break;
        case 6:
            cout << "Выход..." << endl;
            break;
        default:
            cout << "Неверный выбор, введите число от 1 до 6." << endl;
        }
    } while (choice != 6);

    return 0;
}
