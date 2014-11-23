####################################################################
#	This is the Makefile for PHYSICAL LAYER.
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

#DFLAG =
CFLAGS = -g $(DFLAG) -I$(INCLUDE)
# -g to generate symbolic info. used by
#    the debugger.
# DFLAG can be used to turn specific debug
# messages 'on' or 'off'.  Read up on 
# "#ifdef" for more details

SRCS = \
	error.c createcats.c opencats.c closecats.c openrel.c closerel.c findrelnum.c \
	readpage.c flushpage.c writerec.c findrec.c getnextrec.c insertrec.c deleterec.c \
	helpers.c

OBJ = \
	error.o createcats.o opencats.o closecats.o openrel.o closerel.o findrelnum.o \
	readpage.o flushpage.o writerec.o findrec.o getnextrec.o insertrec.o deleterec.o \
	helpers.o

#############################################################
# 	stuff to build the executables
#############################################################

PHYSICAL.o : $(OBJ)
	@echo generating $@
	@ld -r $(OBJ) -o $@

$(OBJ) : $(INCLUDE)/globals.h $(INCLUDE)/defs.h $(INCLUDE)/error.h

error.o : $(INCLUDE)/error.h
createcats.o : $(INCLUDE)/createcats.h
opencats.o : $(INCLUDE)/opencats.h
closecats.o : $(INCLUDE)/closecats.h
openrel.o : $(INCLUDE)/openrel.h
closerel.o : $(INCLUDE)/closerel.h
findrelnum.o : $(INCLUDE)/findrelnum.h
readpage.o : $(INCLUDE)/readpage.h
flushpage.o : $(INCLUDE)/flushpage.h 
writerec.o : $(INCLUDE)/writerec.h
findrec.o : $(INCLUDE)/findrec.h
getnextrec.o : $(INCLUDE)/getnextrec.h
insertrec.o : $(INCLUDE)/insertrec.h
deleterec.o : $(INCLUDE)/deleterec.h
helpers.o : $(INCLUDE)/helpers.h

###############################################################
#  misc
###############################################################

tags:
	ctags $(SRCS) $(INCLUDE)/defs.h $(INCLUDE)/error.h

splint:	
	splint $(SRCS) $(INCLUDE)/defs.h $(INCLUDE)/error.h > lint.out

clean:  # remove all .o files and other garbage
	rm *.o

