SRC = $(wildcard *.cpp)
CXX ?= clang
LDFLAGS ?= "-g -std=c++1y -stdlib=libc++ -lstdc++"

SUBDIRS = src/logservice src/command src/observable

all: subdirs

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ -f makefile.mk run CXX=$(CXX) LDFLAGS=$(LDFLAGS)