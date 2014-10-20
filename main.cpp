#include <iostream>
#include <string>
#include "curlbuffer.h"

#define BOARDLENGTH 1 

using namespace std;

void tryName( int i, string Test)
{
	string Alphabet = "abcdefghijklmnopqrstuvwxyz";
	for ( int j = 0; j < Alphabet.size(); j++)
	{
		Test[i] = Alphabet[j];
		string BoardUrl = "http://8chan.co/";
		BoardUrl.append( Test);
		cout << "\nGrabbing " << BoardUrl << " . . .\n";
		cout << getWebPage( ( char*) BoardUrl.c_str()) << endl;
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
	cout << Test << endl;
	int i;
	tryName( i, Test);
	return 0;
}
