SRC = $(wildcard *.cpp)
CXX ?= clang
LDFLAGS=-g -std=c++1y -stdlib=libc++ -lstdc++

all: example

COMPILE_EXAMPLE = $(OBJS) $(CXX) example.cpp logservice.cpp $(LDFLAGS) -o example.exe $(OBJS)
run:
	$(COMPILE_EXAMPLE) && ./example.exe

example:
	$(COMPILE_EXAMPLE)
