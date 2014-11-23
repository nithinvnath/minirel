####################################################################
#
#	This is the Makefile for creating MINIREL.
#
#
####################################################################


# where to look for the files

HOME = ../

INCLUDE  = $(HOME)/include

ALGEBRA	 = $(HOME)/algebra
SCHEMA	 = $(HOME)/schema
PHYSICAL = $(HOME)/physical

PARSER   = $(HOME)/frontend



DFLAG =
CFLAGS = -g $(DFLAG) -I$(INCLUDE)
# -g to generate symbolic info. used by
#    the debugger.
# DFLAG can be used to turn specific debug
# messages 'on' or 'off'.  Read up on 
# "#ifdef" for more details


#############################################################
# 	stuff to build the executables
#############################################################

SRCS =  main.c

OBJ = main.o 

ALGEBRA.o :
	@cd $(ALGEBRA) ; make $@
	
SCHEMA.o :
	@cd $(SCHEMA) ; make $@

PHYSICAL.o :
	@cd $(PHYSICAL) ; make $@



proj :
	@make ALGEBRA.o
	@make SCHEMA.o
	@make PHYSICAL.o
	@make minirel

minirel : $(ALGEBRA)/ALGEBRA.o $(SCHEMA)/SCHEMA.o $(PHYSICAL)/PHYSICAL.o $(PARSER)/FES.o $(OBJ) 
	@echo generating $@
	@cc $(CFLAGS) $(ALGEBRA)/ALGEBRA.o $(SCHEMA)/SCHEMA.o $(PHYSICAL)/PHYSICAL.o $(PARSER)/FES.o $(OBJ) -o $@


$(OBJ) :  $(INCLUDE)/globals.h $(INCLUDE)/defs.h $(INCLUDE)/error.h

###############################################################
#  misc
###############################################################

clean:  # remove all .o files and other garbage
	rm *.o




