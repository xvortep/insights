CXX = g++
CXXFLAGS = -std=c++20 -O3 -fconstexpr-loop-limit=1200000 -fconstexpr-ops-limit=1000000000000

static: static.cpp
	$(CXX) $(CXXFLAGS) static.cpp -o static

clean:
	rm -f static
