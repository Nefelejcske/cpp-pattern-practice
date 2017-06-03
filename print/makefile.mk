SRC = $(wildcard *.cpp)
CXX = clang
LDFLAGS=-g -std=c++14 -stdlib=libc++ -lstdc++

COMPILE_EXAMPLE = $(OBJS) $(CXX) example.cpp logservice.cpp $(LDFLAGS) -o example.exe $(OBJS)

all: example

run:
	$(COMPILE_EXAMPLE) && ./example.exe

example:
	$(COMPILE_EXAMPLE)
