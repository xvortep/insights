#include <cstdio>
#include <vector>
#include <array>

static volatile int a = 0;

struct Base {
	virtual void name() const = 0;
};

struct D1 : public Base { void name() const { a++; } };
struct D2 : public Base { void name() const { a++; } };
struct D3 : public Base { void name() const { a++; } };
struct D4 : public Base { void name() const { a++; } };
struct D5 : public Base { void name() const { a++; } };
struct D6 : public Base { void name() const { a++; } };

constexpr std::array<D1, 200000> arrD1{};
constexpr std::array<D2, 200000> arrD2{};
constexpr std::array<D3, 200000> arrD3{};
constexpr std::array<D4, 200000> arrD4{};
constexpr std::array<D5, 200000> arrD5{};
constexpr std::array<D6, 200000> arrD6{};

constexpr const Base* getObjectAddress(int index) {
    switch (index % 6) {
        case 0:
            return &arrD1[index / 6];
        case 1:
            return &arrD2[index / 6];
        case 2:
            return &arrD3[index / 6];
        case 3:
            return &arrD4[index / 6];
        case 4:
            return &arrD5[index / 6];
        case 5:
            return &arrD6[index / 6];
        default:
            return nullptr; // Handle unexpected case
    }
}

constexpr std::array<const Base*, 1200000> generateObjects() {
    std::array<const Base*, 1200000> b;
    for (std::size_t i = 0; i < 1200000; ++i) {
        b[i] = getObjectAddress(i);
    }
    return b;
}

void test() {
    static constexpr auto b = generateObjects(); // just constexpr wont work, probably because of the stack

    for (const auto& el: b) {
		el->name();
    }
}

int main() {
	test();
}