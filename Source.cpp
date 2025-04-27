#include "Header.h"

using namespace Nastolki;
using namespace std;

ni::ni(std::string name, std::string vid, int vozrast, std::string sloznost, int chislo_people, int price, ni* next)
    : _name(name), _vid(vid), _vozrast(vozrast), _sloznost(sloznost), _chislo_people(chislo_people), _price(price), _next(next) {
}

string ni::name() { return _name; }
string ni::vid() { return _vid; }
int ni::vozrast() { return _vozrast; }
string ni::sloznost() { return _sloznost; }
int ni::chislo_people() { return _chislo_people; }
int ni::price() { return _price; }
ni* ni::next() { return _next; }
void ni::setNext(ni* next) { _next = next; }

istream& Nastolki::operator >> (istream& in, ni& p) {
    in >> p._name >> p._vid >> p._vozrast >> p._sloznost >> p._chislo_people >> p._price;
    return in;
}

List::List() : _first(nullptr), _last(nullptr), _n(0) {}

List::~List() {
    ni* current = _first;
    while (current) {
        ni* temp = current->next();
        delete current;
        current = temp;
    }
}

void List::push(std::string name, std::string vid, int vozrast, std::string sloznost, int chislo_people, int price) {
    ni* ne = new ni(name, vid, vozrast, sloznost, chislo_people, price);
    if (_n == 0) {
        _first = _last = ne;
    }
    else {
        _last->setNext(ne);
        _last = ne;
    }
    _n++;
}

void List::load(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл не найден. Создание нового файла." << endl;
        ofstream newFile(filename);
        if (!newFile.is_open()) {
            cout << "Ошибка при создании файла." << endl;
            return;
        }
        newFile.close();
        return;
    }

    string name, vid, sloznost;
    int vozrast, chislo_people, price;
    while (file >> name >> vid >> vozrast >> sloznost >> chislo_people >> price) {
        push(name, vid, vozrast, sloznost, chislo_people, price);
    }
    file.close();
}

void List::save(const std::string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка при открытии файла для записи." << endl;
        return;
    }

    ni* current = _first;
    while (current) {
        file << current->name() << " " << current->vid() << " " << current->vozrast() << " "
            << current->sloznost() << " " << current->chislo_people() << " " << current->price() << endl;
        current = current->next();
    }
    file.close();
}

ni* List::get(int index) {
    if (index < 0 || index >= _n) {
        return nullptr;
    }

    ni* current = _first;
    for (int i = 0; i < index; i++) {
        current = current->next();
    }
    return current;
}

void List::remove(int index) {
    if (_n == 0 || index < 0 || index >= _n) {
        cout << "Неверный индекс." << endl;
        return;
    }

    if (index == 0) {
        ni* temp = _first;
        _first = _first->next();
        delete temp;
    }
    else {
        ni* prev = get(index - 1);
        ni* current = prev->next();
        prev->setNext(current->next());
        if (current == _last) {
            _last = prev;
        }
        delete current;
    }
    _n--;
}

void List::print() {
    ni* current = _first;
    int index = 0;
    if (!current) {
        cout << "Список пуст." << endl;
        return;
    }

    while (current) {
        cout << "Индекс: " << index << " " << "Название: " << current->name() << " " << "Тип: " << current->vid() << " "
            << "Возраст: " << current->vozrast() << " " << "Сложность: " << current->sloznost() << " "
            << "Количество игроков: " << current->chislo_people() << " " << "Цена: " << current->price() << endl;
        current = current->next();
        index++;
    }
}

void List::search(std::string vid, int min_price) {
    ni* current = _first;
    bool found = false;

    while (current) {
        if (current->vid() == vid && current->price() >= min_price) {
            cout << "Найдено: Название = " << current->name() << " " << "Цена: " << current->price() << endl;
            found = true;
        }
        current = current->next();
    }

    if (!found) {
        cout << "Товар не найден." << endl;
    }
}

void List::edit(int index) {
    if (_n == 0 || index < 0 || index >= _n) {
        cout << "Неверный индекс." << endl;
        return;
    }

    ni* current = get(index);
    if (!current) {
        cout << "Ошибка!" << endl;
        return;
    }

    cout << "Введите новое название, новый тип, новый минимальный возраст игрока, новую сложность, новое количество игроков, новую цену товара: ";
    cin >> *current;
}

int List::size() {
    return _n;
}
