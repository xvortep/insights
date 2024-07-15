CXX = g++
CXXFLAGS = -std=c++20 -O3 -fconstexpr-loop-limit=1200000 -fconstexpr-ops-limit=1000000000000

dynamic: dynamic.cpp
	$(CXX) $(CXXFLAGS) dynamic.cpp -o dynamic

clean:
	rm -f dynamic
