#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct listinfo {
	string Content[1000];
	int Size;
};

void sortListPath( string ListPath)
{
	string Cmd = "sort ";
	Cmd.append( ListPath);
	Cmd.append( " > ");
	Cmd.append( ListPath);
	Cmd.append( ".temp && mv ");
	Cmd.append( ListPath);
	Cmd.append( ".temp ");
	Cmd.append( ListPath);
	system( Cmd.c_str());
}

struct listinfo matchList( struct listinfo ListBig, struct listinfo ListSmall)
{
	for ( int j = 0; j < ListBig.Size; j++)
	{
		if ( ListBig.Content[j].compare( "") != 0)
		{
			for ( int i = 0; i < ListSmall.Size; i++)
			{
				if ( ListSmall.Content[i].compare( "") != 0)
				{
					if ( ListSmall.Content[i].compare( ListBig.Content[j]) == 0)
					{
						ListSmall.Content[i] = "";
						ListBig.Content[j] = "";
					}
				}
			}
		}
	}
	return ListBig;
}

void printList( struct listinfo List)
{
	for ( int i = 0; i < List.Size; i++)
	{
		if ( List.Content[i].compare( "") != 0)
		{
			cout << List.Content[i] << endl;
			cout.flush();
		}
	}
}

int main( int argc, char** argv)
{
	if ( argc != 3)
	{
		cerr << "usage: " << argv[0] << " /path/to/list1.txt /path/to/list2.txt\n";
		return -1;
	}
	string ListPath1 = ( string) argv[1];
	string ListPath2 = ( string) argv[2];
	
	fstream File;
	File.open( ( const char*) ListPath1.c_str(), fstream::in);
	File.close();
	if ( File.fail())
	{
		cerr << "Error: one or more of the files specified do not exist" << endl;
		return -1;
	}
	File.open( ( const char*) ListPath2.c_str(), fstream::in);
	File.close();
	if ( File.fail())
	{
		cerr << "Error: one or more of the files specified do not exist" << endl;
		return -1;
	}

	sortListPath( ListPath1);
	sortListPath( ListPath2);

	struct listinfo List1;
	struct listinfo List2;

	File.open( ( const char*) ListPath1.c_str(), fstream::in);
	for ( List1.Size = 0; getline( File, List1.Content[List1.Size]); List1.Size++) {}
	File.close();

	File.open( ( const char*) ListPath2.c_str(), fstream::in);
	for ( List2.Size = 0; getline( File, List2.Content[List2.Size]); List2.Size++) {}
	File.close();
	
	if ( List1.Size > List2.Size)
	{
		printList( matchList( List1, List2));
	}
	else
	{
		printList( matchList( List2, List1));
	}
	
	return 0;
}
