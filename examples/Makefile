# Author:  Tan Menglong <tanmenglong@gmail.com>
# Date:    Wed Aug  8 13:44:35 2012
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include ../Makefile.env

BUILD_TARGETS = zh_log_1_example zh_log_2_example

INC = -I../include -I../src
LIB = -lpthread

OBJ = ../src/libzhuhai.a

TEST_SRC = $(wildcard *_example.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

.PHONY : all clean src check

all : $(BUILD_TARGETS)

clean :
	rm -rf $(TEST_OBJ) $(BUILD_TARGETS)

%_example : %_example.o
	$(LINK) -o $@ $^ $(OBJ) $(LIB)

check : all
	valgrind --leak-check=full --show-reachable=yes ./zh_log_1_example
	valgrind --leak-check=full --show-reachable=yes ./zh_log_2_example
