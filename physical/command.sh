#!/bin/bash
gcc -c -g flushpage.c 
gcc -c -g helpers.c 
gcc -c -g readpage.c
gcc -c -g getnextrec.c
gcc -c -g readpage.c 
gcc -c -g flushpage.c
gcc -c -g opencats.c
gcc -c -g findrec.c
gcc -c -g openrel.c
gcc -c -g error.c
gcc -c -g createcats.c
gcc -c -g findrelnum.c
gcc -c -g closerel.c
gcc -g -c closecats.c
gcc -g -c insertrec.c
gcc -g -c ../schema/destroydb.c
gcc -g -c ../schema/opendb.c
gcc -g -c ../schema/createdb.c
gcc -g -c ../schema/closedb.c
gcc -g -c ../schema/print.c
gcc -g -c ../schema/create.c
gcc -g -c ../algebra/insert.c

gcc -g main.c flushpage.o readpage.o getnextrec.o error.o helpers.o findrec.o opencats.o openrel.o createcats.o findrelnum.o closerel.o closecats.o opendb.o destroydb.o createdb.o closedb.o print.o create.o insert.o insertrec.o
