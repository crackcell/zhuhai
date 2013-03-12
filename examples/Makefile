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

ZH_ROOT = ../

INC = -I../include/ -I./ -I$(SCWS)/include
LIB = -levent \
	-lpthread -ltcmalloc
ifeq ($(OS), Linux)
	LIB += -lm
endif

OBJ = ../src/libzhuhai_debug.a

TEST_SRC = $(wildcard *_example.cpp)
TEST_OBJ = $(patsubst %.cpp, %.o, $(TEST_SRC))
BUILD_TARGETS = $(patsubst %.cpp, %, $(TEST_SRC))

.PHONY : all clean src check

all : $(BUILD_TARGETS)

clean :
	rm -rf $(TEST_OBJ) $(BUILD_TARGETS)

%_example : %_example.o
	$(LINK) -o $@ $^ $(OBJ) $(LIB) -D_DEBUG

check : all
	for file in $(wildcard *example); \
		do valgrind --leak-check=full ./$$file; \
	done;
