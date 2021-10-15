#
# Makefile for project 2
# Created by Doonlayatis(DOON)
# ID 62070503421
#

CC	= gcc

CFLAG	= -g

OBJ	=main.o filemodify.o filesearch.o filereadwrite.o validation.o

EXES	=main$(EXECEXT)

ALL : $(EXES)

filemodify.o	: filemodify.c filemodify.h
	$(CC) $(CFLAG) -c filemodify.c

filesearch.o	: filesearch.c filesearch.h
	$(CC) $(CFLAG) -c filesearch.c

filereadwrite.o	: filereadwrite.c filereadwrite.h
	$(CC) $(CFLAG) -c filereadwrite.c

validation.o	: validation.c validation.h
	$(CC) $(CFLAG) -c validation.c

main$(EXECEXT)	: main.o filemodify.o filesearch.o filereadwrite.o validation.o
	$(CC) $(CFLAG) -o main$(EXECEXT) main.o filemodify.o filesearch.o filereadwrite.o validation.o

clean	:
	-@rm $(OBJ) $(EXEs)


