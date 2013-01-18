# Author:  Tan Menglong <tanmenglong@gmail.com>
# Date:    Sun Aug 26 17:04:21 2012
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include ../Makefile.env

ZH_ROOT = ../

BUILD_TARGETS = libzhuhai.a libzhuhai_debug.a

INC = -I../include/ -I./ -I$(SCWS)/include

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
OBJ_DEBUG = $(patsubst %.cpp, %_d.o, $(SRC))

.PHONY : all clean

all : $(BUILD_TARGETS)

libzhuhai.a : $(OBJ)
ifeq ($(OS), Darwin)
	libtool -static -o $@ $^
else
	ar -cr -o $@ $^
endif

libzhuhai_debug.a : $(OBJ_DEBUG)
ifeq ($(OS), Darwin)
	libtool -static -o $@ $^
else
	ar -cr -o $@ $^
endif

clean :
	rm -rf $(OBJ) $(OBJ_DEBUG) $(BUILD_TARGETS)
