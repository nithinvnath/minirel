####################################################################
#	This is the Makefile for FRONTEND.
#
#	If you want to add a file, add it to both the SRC and OBJ lists.
#	Use a backslash for continuation into the next line.
#
####################################################################

# where to look for the header files
INCLUDE = .

####################################################################
# FLAGS for the C compiler
####################################################################
DFLAG = 
CFLAGS = -g $(DFLAG) -I$(INCLUDE)
# -g to generate symbolic info. used by
#    the debugger.
# DFLAG can be used to turn specific debug
# messages 'on' or 'off'.  Read up on 
# "#ifdef" for more details


SRCS = \
	fes.c

OBJ = \
	fes.o


#############################################################
# 	stuff to build the executables
#############################################################

FES.o : $(OBJ)
	@echo generating $@
	@ld -r $(OBJ) -o $@

$(OBJ) : $(INCLUDE)/fes.h

###############################################################
#  misc
###############################################################

tags:
	ctags -t $(SRCS) $(INCLUDE)/fes.h

lint:	
	lint $(SRCS) $(INCLUDE)/fes.h > lint.out

clean:  # remove all .o files and other garbage
	rm *.o


