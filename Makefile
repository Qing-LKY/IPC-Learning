export CC := gcc
export INCLUDE := include
export CFLAGS := -g -O2
export LDFLAGS := -lpthread -lreadline
export LDFLAGS_STATIC := -static -lpthread -lreadline -ltermcap -lncurses
export TARGET := test
export TARGET_STATIC := test-static

export SHELL := /bin/sh

all:
	$(MAKE) -C src

.phony: clean static

static:
	$(MAKE) -C src static

clean:
	$(MAKE) -C src clean
	$(RM) $(TARGET) $(TARGET_STATIC)