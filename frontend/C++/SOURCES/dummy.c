
/*
** Dummy program to test the parser
**
*/


# include <iostream.h>

extern int parser();

void main()
{
	cout << "Welcome to MINIREL" << endl;
    	parser();
	cout << "GoodBye from MINIREL" << endl;
}

int Select(int argc, char **argv)
{
	cout << "Calling from Select" << endl;
	return 1;
}	

int Join( int argc, char **argv)
{
	cout << "Calling from Join" << endl;
  	return 1;
}

int Insert( int argc, char **argv)
{
	cout << "Calling from Insert" << endl;
  	return 1;
}

int Delete( int argc, char **argv)
{
	cout << "Calling from Delete" << endl;
  	return 1;
}

int BuildIndex( int argc, char **argv)
{
	cout << "Calling from BuildIndex" << endl;
  	return 1;
}

int DropIndex( int argc, char **argv)
{
	cout << "Calling from DropIndex" << endl;
  	return 1;
}

int Quit( int argc, char **argv)
{
	cout << "Calling from Quit" << endl;
  	return 1;
}

int Print( int argc, char **argv)
{
	cout << "Calling from Print" << endl;
  	return 1;
}

int Load( int argc, char **argv)
{
	cout << "Calling from Load" << endl;
  	return 1;
}

int Destroy( int argc, char **argv)
{
	cout << "Calling from Destroy" << endl;
  	return 1;
}

int Create( int argc, char **argv)
{
	cout << "Calling from Create" << endl;
  	return 1;
}

int Project( int argc, char **argv)
{
	cout << "Calling from Project" << endl;
  	return 1;
}


int CreateDB( int argc, char **argv)
{
  return 1;
}


int DestroyDB( int argc, char **argv)
{
  return 1;
}

int OpenDB( int argc, char **argv)
{
  return 1;
}

int CloseDB( int argc, char **argv)
{
  return 1;
}
