####################################################################
#	This is the Makefile for SCHEMA layer.
#
#	If you want to add a file, add it to both the SRC and OBJ lists.
#	Use a backslash for continuation into the next line.
#
####################################################################

####################################################################
# FLAGS for the C compiler
####################################################################

# where to look for the header files
INCLUDE = ../include

DFLAG =
CFLAGS = -g $(DFLAG) -I$(INCLUDE)
# -g to generate symbolic info. used by
#    the debugger.
# DFLAG can be used to turn specific debug
# messages 'on' or 'off'.  Read up on 
# "#ifdef" for more details

SRCS = \
	createdb.c opendb.c closedb.c destroydb.c quit.c \
	create.c destroy.c load.c print.c sort.c buildindex.c dropindex.c

OBJ = \
	createdb.o opendb.o closedb.o destroydb.o quit.o \
        create.o destroy.o load.o print.o sort.o buildindex.o dropindex.o

#############################################################
# 	stuff to build the executables
#############################################################

SCHEMA.o : $(OBJ)
	@echo generating $@
	@ld -r $(OBJ) -o $@

$(OBJ) : $(INCLUDE)/globals.h $(INCLUDE)/defs.h $(INCLUDE)/error.h

###############################################################
#  misc
###############################################################

tags:
	ctags -t $(SRCS) $(INCLUDE)/defs.h $(INCLUDE)/error.h

lint:	
	lint $(SRCS) $(INCLUDE)/defs.h $(INCLUDE)/error.h > lint.out

clean:  # remove all .o files and other garbage
	rm *.o
