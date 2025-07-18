// https://godbolt.org/z/8n9dYh45h

#include <iostream>
#include <cstdint>
#include <cstring>
#include <memory>
#include <functional>
#include <variant>
#include <map>
#include <iostream>

template<class t>
struct variator {

    variator(t& obj) : holder(obj) {}
    variator(int obj) : holder(obj) {}

    t operator[](int a) {
        return *std::get<t>(holder).next;
    }

    operator int() {
        return std::get<int>(holder);
    }

    std::variant<int, t> holder;
};

struct type {
    type(int a) : value(a) {}
    
    type* next = nullptr;

    int value;


    variator<type> operator[](int a) {
        if (!a)
            return *next;
        else
            return next->value;
    }
};




int main() {
    type a(1), s(2), d(3), f(4);

    a.next = &s;
    s.next = &d;
    d.next = &f;

    int h = a[0][0][1];

    std::cout << h << std::endl;

    return 0;
}
