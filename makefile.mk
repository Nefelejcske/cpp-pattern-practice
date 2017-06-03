SRC = $(wildcard *.cpp)
CXX ?= clang
LDFLAGS ?= "-g -std=c++1y -stdlib=libc++ -lstdc++"

SUBDIRS = print

all: subdirs

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ -f makefile.mk run SRC=$(SRC) CXX=$(CXX) LDFLAGS=$(LDFLAGS)