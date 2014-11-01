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

gcc -g main.c flushpage.o readpage.o getnextrec.o error.o helpers.o findrec.o opencats.o openrel.o createcats.o findrelnum.o closerel.o
