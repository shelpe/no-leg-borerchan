#include <fstream>
#include <iostream>
#include <string>
#include "curlbuffer.h"

#define BOARDLENGTH 3 

using namespace std;

bool reactToPage( string BoardContent)
{
	if ( BoardContent == "no_referers")
	{
		cerr << "Please put newline separated http referers in 'referers.txt'.  Exiting...\n";
		exit(0);
	}
	else if ( BoardContent == "no_useragents")
	{
		cerr << "Please put newline separated http user agents in 'useragents.txt'.  Exiting...\n";
		exit(0);
	}
	else if ( BoardContent.find( "<title>404 Not Found</title>") != -1)
	{
		return false;
	}
	return true;
}	

void tryName( int i, string Test)
{
	string Alphabet = "abcdefghijklmnopqrstuvwxyz1234567890";
	for ( int j = 0; j < Alphabet.size(); j++)
	{
		Test[i] = Alphabet[j];
		if ( i == Test.size() - 1)
		{
			string BoardUrl = "http://8chan.co/";
			BoardUrl.append( Test);
			string BoardContent = ( string) getWebPage( ( char*) BoardUrl.c_str());
			if ( reactToPage( BoardContent))
			{
				cout << Test << endl;
				cout.flush();
			}
		}
		else
		{
			tryName( i + 1, Test);
		}
	}
}	

int main()
{
	string Test;
	Test.resize( BOARDLENGTH);
	Test.assign( Test.size(), 'a');
	tryName( 0, Test);
	return 0;
}
