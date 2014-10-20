#include <iostream>
#include <string>
#include "curlbuffer.h"

#define BOARDLENGTH 1 

using namespace std;

bool reactToPage( string BoardContent)
{
	if ( BoardContent.find( "<title>404 Not Found</title>") != -1)
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
		if ( i == Test.size() - 1)
		{
			Test[i] = Alphabet[j];
			string BoardUrl = "http://8chan.co/";
			BoardUrl.append( Test);
			string BoardContent = ( string) getWebPage( ( char*) BoardUrl.c_str());
			if ( reactToPage( BoardContent))
			{
				cout << "Board /" << Test << "/ found (" << BoardUrl << ")\n";
			}
			else
			{
				cout << "Board /" << Test << "/ not found\n";
			}
		}
		if ( i < Test.size() - 1)
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
