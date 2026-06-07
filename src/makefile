CXX=g++
CXXFLAGS=-std=c++17 -O2

SRC=main.cpp \
    fermat.cpp \
    miller_rabin.cpp \
    ensemble.cpp \
    carmichael.cpp \
    benchmark.cpp \
    rsa.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o prime_engine

clean:
	rm -f prime_engine
