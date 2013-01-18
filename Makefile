# Author:  Tan Menglong <tanmenglong@gmail.com>
# Date:    Sun Aug 26 17:03:29 2012
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include Makefile.env

.PHONY : all output test example clean help

all : output

3rd :
	make -C third

output :
	make -C src
	make -C unittest
	make -C examples
	mkdir -p output/lib output/include output/examples
	cp src/libzhuhai.a output/lib
	cp -r include/* output/include/
	cp examples/* output/examples/

test :
	make -C unittest
	make test -C unittest

check :
	make check -C unittest

clean :
	rm -rf output
	make clean -C src
	make clean -C unittest
	make clean -C examples

help :
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  clean     clean objects and the executable file.'
	@echo '  help      print this message.'
	@echo
