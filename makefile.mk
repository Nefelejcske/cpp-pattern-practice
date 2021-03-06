SRC = $(wildcard *.cpp)
CXX ?= clang
LDFLAGS ?= -g -std=c++1y -stdlib=libc++ -lstdc++ -lm -lpthread

SUBDIRS = logservice command observable thread object_pool

all: subdirs

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C src/$@ -f makefile.mk run CXX=$(CXX) LDFLAGS="$(LDFLAGS)"
