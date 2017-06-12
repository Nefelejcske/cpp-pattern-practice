SRC_LOGSERVICE = $(wildcard ../../logservice/logservice.cpp)
SRC = $(wildcard *.cpp)
CXX ?= clang
LDFLAGS ?= -g -std=c++1y -stdlib=libc++ -lstdc++ -lm -lpthread
COMPILE_EXAMPLE = $(OBJS) $(CXX) $(SRC_LOGSERVICE) $(SRC) $(LDFLAGS) -o example.exe $(OBJS)

SUBDIRS = bland actor

run: subdirs

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ -f makefile.mk run CXX=$(CXX) LDFLAGS="$(LDFLAGS)"
