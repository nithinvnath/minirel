gcc -c -g flushpage.c  
gcc -c -g readpage.c
gcc -c -g getnextrec.c
gcc -c -g readpage.c 
gcc -c -g flushpage.c
gcc -c -g opencats.c
gcc -g main1.c flushpage.o readpage.o getnextrec.o error.o helpers.o findrec.o opencats.o
