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

BUILD_TARGETS = libzhuhai.a

INC = -I../include -I./

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

.PHONY : all clean

all : $(BUILD_TARGETS)

libzhuhai.a : $(OBJ)
ifeq ($(ARCH), Darwin)
	libtool -static -o $@ *.o
else
	ar -cr -o $@ *.o
endif

clean :
	rm -rf $(OBJ) $(BUILD_TARGETS)
