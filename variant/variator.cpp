// https://godbolt.org/z/jxGxjE4K3

#include <cstdint>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <variant>

template <class def, class... types>
struct variator {
    variator(def obj) : holder(obj) {}

    template <class t>
    variator(t obj) : holder(obj) {
        static_assert(
            std::is_same_v<t, def> || (std::is_same_v<t, types> || ...),
            "the type requested is not supported for this template");
    }

    variator<def, types...> operator[](std::string str) { return std::get<def>(holder)[str]; }

    template <class t>
    operator t() {
        static_assert(
            std::is_same_v<t, def> || (std::is_same_v<t, types> || ...),
            "the type requested is not supported for this template");

        return std::get<t>(holder);
    }

    std::variant<def, types...> holder;
};

struct type {
    type* next = nullptr;

    int value;
    char character;

    // default backup type has to be first
    using v_t = variator<type, int, char>;

    v_t operator[](std::string a) {
        if (a == "")
            return *next;
        else if (a == "v")
            return next->value;
        else if (a == "c")
            return next->character;
        else
            return *next;
    }
};

int main() {
    type a, s, d, f;

    a.next = &s;
    s.next = &d;
    d.next = &f;

    a.value = 1;
    s.value = 2;
    d.value = 3;
    f.value = 4;

    a.character = 'a';
    s.character = 's';
    d.character = 'd';
    f.character = 'f';

    int h = a[""][""]["v"];
    char c = a[""]["c"];

    // this should fail
    // h = a["c"];

    std::cout << h << std::endl;
    std::cout << c << std::endl;

    return 0;
}
