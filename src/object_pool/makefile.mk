SRC_LOGSERVICE = $(wildcard ../logservice/logservice.cpp)
SRC = $(wildcard *.cpp)
CXX ?= clang
LDFLAGS ?= -g -std=c++1y -stdlib=libc++ -lstdc++

all: example

COMPILE_EXAMPLE = $(OBJS) $(CXX) $(SRC_LOGSERVICE) $(SRC) $(LDFLAGS) -o example.exe $(OBJS)
run:
	$(COMPILE_EXAMPLE) && ./example.exe

example:
	$(COMPILE_EXAMPLE)
