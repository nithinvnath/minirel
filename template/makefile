####################################################################
#	This is a sample makefile for the physical layer.
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
	error.c createcats.c opencats.c closecats.c openrel.c closerel.c findrelnum.c \
	readpage.c flushpage.c writerec.c findrec.c getnextrec.c insertrec.c deleterec.c

OBJ = \
	error.o createcats.o opencats.o closecats.o openrel.o closerel.o findrelnum.o \
	readpage.o flushpage.o writerec.o findrec.o getnextrec.o insertrec.o deleterec.o

#############################################################
# 	stuff to build the executables
#############################################################

PHYSICAL.o : $(OBJ)
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

