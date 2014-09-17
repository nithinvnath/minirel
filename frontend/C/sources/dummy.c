
/*
** Dummy program to test the parser
**
*/


# include <stdio.h>

extern int parser();

void main()
{
	printf( "\nWelcome to MINIREL\n\n" );
    	parser();
	printf( "\nGoodBye from MINIREL\n\n" );
}

int Select(int argc, char **argv)
{
	printf( "Calling from Select\n" );
	return 1;
}	

int Join( int argc, char **argv)
{
	printf( "Calling from Join\n" );
  	return 1;
}

int Insert( int argc, char **argv)
{
	printf( "Calling from Insert\n" );
  	return 1;
}

int Delete( int argc, char **argv)
{
	printf( "Calling from Delete\n" );
  	return 1;
}

int BuildIndex( int argc, char **argv)
{
	printf( "Calling from BuildIndex\n" );
  	return 1;
}

int DropIndex( int argc, char **argv)
{
	printf( "Calling from DropIndex\n" );
  	return 1;
}

int Quit( int argc, char **argv)
{
	printf( "Calling from Quit\n" );
  	return 1;
}

int Print( int argc, char **argv)
{
	printf( "Calling from Print\n" );
  	return 1;
}

int Load( int argc, char **argv)
{
	printf( "Calling from Load\n" );
  	return 1;
}

int Destroy( int argc, char **argv)
{
	printf( "Calling from Destroy\n" );
  	return 1;
}

int Create( int argc, char **argv)
{
	printf( "Calling from Create\n" );
  	return 1;
}

int Project( int argc, char **argv)
{
	printf( "Calling from Project\n" );
  	return 1;
}


int CreateDB( int argc, char **argv)
{
	printf( "Calling from CreateDB\n" );
  	return 1;
}


int DestroyDB( int argc, char **argv)
{
	printf( "Calling from DestroyDB\n" );
  	return 1;
}

int OpenDB( int argc, char **argv)
{
	printf( "Calling from OpenDB\n" );
  	return 1;
}

int CloseDB( int argc, char **argv)
{
	printf( "Calling from CloseDB\n" );
  	return 1;
}
