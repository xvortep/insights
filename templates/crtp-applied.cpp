#include <iostream>
#include <functional>
#include <tuple>
#include <map>
#include <string_view>
#include <functional>

template<typename t>
concept initable = requires {
    {t::onInit} -> std::convertible_to<std::function<void(t*)>>;
};

template<class derivate>
struct base {
    int def = 7;
    
    void call() {
        if constexpr (initable<derivate>) {
            derivate::onInit(static_cast<derivate*>(this));
        }
    }
};

struct a : public base<a> {
    double d;
    static inline std::function<void(a*)> onInit = [](a* other)->void{std::cout << " d = " << other->d << std::endl;};
};

struct b : public base<b> {
    std::string a;
    static inline std::function<void(b*)> onInit = [](b* other)->void{std::cout << " a = " << other->a << std::endl;};
};

struct c: public base<c> {
    std::string ag;
};

struct fail {
    std::string def;
};

template<class d>
concept derived = std::derived_from<d, base<d>>;

template<derived objtype>
void g(objtype& obj) {
    obj.call();
}

void foo(a& obj) {
    std::cout << "d " << obj.d << " def " << obj.def << std::endl;
    obj.call();
}

int main() {
    a oa; oa.d = 6; oa.call();

    a::onInit = [](a* other)->void{std::cout << "nista" << std::endl;};

    oa.call();

    std::cout << oa.def << std::endl;

    b ob; ob.a = "asdf"; ob.call();


    std::cout << "**********\n\n\n";

    foo(oa);

    g(oa);

    g(ob);

    fail f;

    c oc;

    g(oc);
    // g(f);
}
