####################################################################
#	This is the Makefile for ALGEBRA layer.
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
	insert.c delete.c join.c project.c select.c 

OBJ = \
	insert.o delete.o join.o project.o select.o

#############################################################
# 	stuff to build the executables
#############################################################

ALGEBRA.o : $(OBJ)
	@echo generating $@
	@ld -r $(OBJ) -o $@

$(OBJ) : $(INCLUDE)/globals.h $(INCLUDE)/defs.h $(INCLUDE)/error.h 

insert.o : $(INCLUDE)/insert.h
delete.o : $(INCLUDE)/delete.h
join.o : $(INCLUDE)/join.h
project.o : $(INCLUDE)/project.h
select.o : $(INCLUDE)/select.h

###############################################################
#  misc
###############################################################

tags:
	ctags -t $(SRCS) $(INCLUDE)/defs.h $(INCLUDE)/error.h

splint:	
	splint $(SRCS) $(INCLUDE)/defs.h $(INCLUDE)/error.h > lint.out

clean:  # remove all .o files and other garbage
	rm *.o
