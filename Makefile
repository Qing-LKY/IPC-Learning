export CC := gcc
export INCLUDE := include
export CFLAGS := -g -O2
export LDFLAGS := -lpthread
export TARGET := test

export SHELL := /bin/sh

all:
	$(MAKE) -C src

.phony: clean

clean:
	$(MAKE) -C src clean
	$(RM) $(TARGET)