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

INC = -I../include -I../src
LIB = -lgtest -lpthread
ifeq ($(OS), Linux)
	LIB += -lm
endif

#OBJ = ../src/libzhuhai.a

TEST_SRC = $(wildcard *_test.cpp)
TEST_OBJ = $(patsubst %.cpp, %.o, $(TEST_SRC))
BUILD_TARGETS = $(patsubst %.cpp, %, $(TEST_SRC))

.PHONY : all clean src check

all : $(BUILD_TARGETS)

test : 
	for file in $(wildcard *_test); \
		do ./$$file; \
	done;

clean :
	rm -rf $(TEST_OBJ) $(BUILD_TARGETS)

%_test : %_test.o
	$(LINK) -o $@ $^ $(OBJ) $(LIB)

check : $(BUILD_TARGETS)
	for file in $(wildcard *SUITE); \
		do valgrind --leak-check=full ./$$file; \
	done;
