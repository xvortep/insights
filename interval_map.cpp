#include <iostream>
#include <map>

template <typename K, typename V>
class interval_map {
  friend void IntervalMapTest();
  V m_valBegin;

 public:
  std::map<K, V> m_map;

  // constructor associates whole range of K with val
  template <typename V_forward>
  interval_map(V_forward &&val) : m_valBegin(std::forward<V_forward>(val)) {}

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Conforming to the C++ Standard Library conventions, the interval
  // includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  // !!! the key is supposed to be associated with the beginning of the interval
  template <typename V_forward>
  void assign(K const &keyBegin, K const &keyEnd, V_forward &&val)
    requires(std::is_same<std::remove_cvref_t<V_forward>, V>::value)
  {
    if (!(keyBegin < keyEnd)) return;

    auto it = m_map.upper_bound(keyEnd);

    if (it != m_map.end() && it != m_map.begin()) {
      --it;
      auto &val = it->second;
      m_map.insert_or_assign(keyEnd, std::forward<decltype(val)>(val));
    } else {
      it = m_map.emplace(keyEnd, std::forward<decltype(m_valBegin)>(m_valBegin))
               .first;
      if (it != m_map.begin()) --it;
    }

    while (it != m_map.end() && !(it->first < keyBegin) && it->first < keyEnd) {
      it = m_map.erase(it);
      if (it != m_map.begin() && it != m_map.end()) --it;
    }

    m_map.insert_or_assign(keyBegin, std::forward<decltype(val)>(val));
  }

  // look-up of the value associated with key
  V const &operator[](K const &key) const {
    auto it = m_map.upper_bound(key);
    if (it == m_map.begin()) {
      return m_valBegin;
    } else {
      return (--it)->second;
    }
  }
};

int main() {
  interval_map<int, char> im('x');
  // im.m_map[2] = 'z';

  im.assign(3, 10, 'y');
  im.assign(2, 5, 's');
  im.assign(4, 7, 'f');
  im.assign(5, 7, 'h');
  im.assign(3, 10, 'y');
  im.assign(3, 10, 'y');
  im.assign(2, 5, 's');
  im.assign(4, 7, 'f');
  im.assign(12, 13, 'e');
  im.assign(13, 14, 'r');
  im.assign(-3, 20, 'x');

  // im.assign(1, 15, 'a');
  // im.assign(3, 13, 'b');
  // im.assign(5, 11, 'c');
  // im.assign(7, 9, 'd');

  // im.assign(3, 10, 'g');
  // im.assign(3, 5, 'r');

  // im.assign(12, 18, 'g');
  // im.assign(3, 10, 'g');

  // im.assign(12, 18, 'q');
  // im.assign(12, 13, 'g');
  // im.assign(12, 13, 'h');

  // im.assign(10, 13, 'v');
  // im.assign(12, 13, 'q');

  // im.m_map[15] = 'x';
  // im.m_map[1] = 'a';
  // im.m_map[13] = 'a';
  // im.m_map[3] = 'b';
  // im.m_map[11] = 'b';
  // im.m_map[5] = 'c';
  // im.m_map[9] = 'c';
  // im.m_map[7] = 'd';

  // std::cout << im[4] << std::endl;

  for (int i = -20; i < 20; i++) {
    std::cout << "im [" << i << "] = " << im[i] << std::endl;
  }

  return 0;
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.