#include <iostream>
#include <atomic>
#include <tuple>
#include <string>

template<class... ts>
class lazy {
public:
    template<typename t>
    auto& get() {
        if (std::get<t*>(objs) == nullptr) {
            return *(std::get<t*>(objs) = new t());
        }
        return *std::get<t*>(objs);
    }

    template<typename t>
    void set(t&& obj) {
        std::cout << "move\n";
        (get<t>()) = obj;
    }

    template<typename t>
    void set(const t& obj) {
        std::cout << "copy\n";
        (get<t>()) = obj;
    }

private:
    std::tuple<ts*...> objs;
};

class someimpl : public lazy<int, std::string> {
    public:
    void writeString(std::string&& str) {
        set<std::string>(std::forward<decltype(str)>(str));
    }
    void printString() {
        std::cout << get<std::string>() << std::endl;
    }
};

int main() {

    // lazy<int, bool, double> l;

    // auto i = l.get<int>();

    std::string ss = "fda";

    someimpl s;
    s.writeString(std::move(ss));
    s.writeString("asdf");
    s.printString();
}
