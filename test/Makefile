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

BUILD_TARGETS = zh_log_SUITE zh_linkedlist_SUITE zh_bitops_SUITE

INC = -I../include -I../src
LIB = -lcunit -lpthread

OBJ = ../src/libzhuhai.a

TEST_SRC = $(wildcard *_test.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))

.PHONY : all clean src check

all : $(BUILD_TARGETS)

clean :
	rm -rf $(TEST_OBJ) $(BUILD_TARGETS)

%_SUITE : %_SUITE.o
	$(LINK) -o $@ $^ $(OBJ) $(LIB)

check : $(BUILD_TARGETS)
	for file in $(wildcard *SUITE); \
		do valgrind --leak-check=full ./$$file; \
	done;
