#include <array>
#include <cstdio>
#include <variant>
#include <vector>

static volatile int a = 0;

template <class Derived> struct Base {
  constexpr Base() = default;
  constexpr Base(const Base &) = default;
  constexpr Base &operator=(const Base &) = default;
  void name() const { (static_cast<const Derived *>(this))->impl(); }
};
struct D1 : public Base<D1> {
  constexpr D1() = default;
  constexpr D1(const D1 &) = default;
  constexpr D1 &operator=(const D1 &) = default;
  void impl() const { a++; }
};
struct D2 : public Base<D2> {
  constexpr D2() = default;
  constexpr D2(const D2 &) = default;
  constexpr D2 &operator=(const D2 &) = default;
  void impl() const { a++; }
};
struct D3 : public Base<D3> {
  constexpr D3() = default;
  constexpr D3(const D3 &) = default;
  constexpr D3 &operator=(const D3 &) = default;
  void impl() const { a++; }
};
struct D4 : public Base<D4> {
  constexpr D4() = default;
  constexpr D4(const D4 &) = default;
  constexpr D4 &operator=(const D4 &) = default;
  void impl() const { a++; }
};
struct D5 : public Base<D5> {
  constexpr D5() = default;
  constexpr D5(const D5 &) = default;
  constexpr D5 &operator=(const D5 &) = default;
  void impl() const { a++; }
};
struct D6 : public Base<D6> {
  constexpr D6() = default;
  constexpr D6(const D6 &) = default;
  constexpr D6 &operator=(const D6 &) = default;
  void impl() const { a++; }
};

using ds_t = std::variant<D1, D2, D3, D4, D5, D6>;

constexpr std::array<ds_t, 6 * 200000> generateObjects() {
  std::array<ds_t, 6 * 200000> b{};
  for (int i = 0; i < 6 * 200000; i++) {
    switch (i % 6) {
    case 0:
      b[i] = ds_t(D1{});
      break;
    case 1:
      b[i] = ds_t(D2{});
      break;
    case 2:
      b[i] = ds_t(D3{});
      break;
    case 3:
      b[i] = ds_t(D4{});
      break;
    case 4:
      b[i] = ds_t(D5{});
      break;
    case 5:
      b[i] = ds_t(D6{});
      break;
    }
  }
  return b;
}

void test() {
  constexpr auto b = generateObjects();

  for (const auto &el : b) {
    std::visit([](auto &&e) { return e.name(); }, el);
  }
}

int main() { test(); }
