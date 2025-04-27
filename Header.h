#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>

namespace Nastolki {
    class ni
    {
        std::string _name;
        std::string _vid;
        int _vozrast;
        std::string _sloznost;
        int _chislo_people;
        int _price;
        ni* _next;
    public:
        ni() = default;
        ni(std::string name, std::string vid, int vozrast, std::string sloznost, int chislo_people, int price, ni* next = nullptr);
        std::string name();
        std::string vid();
        int vozrast();
        std::string sloznost();
        int chislo_people();
        int price();
        ni* next();
        void setNext(ni* next);
        friend std::istream& operator >> (std::istream& in, ni& p);
    };

    class List {
        ni* _first;
        ni* _last;
        int _n;
    public:
        List();
        ~List();
        int size();
        void push(std::string name, std::string vid, int vozrast, std::string sloznost, int chislo_people, int price);
        void load(const std::string& filename);
        void save(const std::string& filename);
        ni* get(int index);
        void remove(int index);
        void print();
        void search(std::string vid, int min_price);
        void edit(int index);
        
    };
}
