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

output :
	make -C src
	make -C test
	make -C examples
	mkdir -p output

clean :
	rm -rf output
	make clean -C src
	make clean -C test
	make clean -C examples

help :
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  clean     clean objects and the executable file.'
	@echo '  help      print this message.'
	@echo
