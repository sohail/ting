#
#Makefile
#

DEFAULT	:	all
.PHONY	:	clean

all	:	ting

ting	:	main.o 
		g++ main.o -o ting

main.o	:	main.cc stuff.h main.h parse_args.h build_header.h local_connect.h
		g++ -c main.cc -o main.o	

clean	:
	rm -v -f *.o
	rm -v -f ting


