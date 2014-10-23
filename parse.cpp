#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <curl/curl.h>
#include <jsmn.h>
#include "curlbuffer.h"

#define BOARDLENGTH 2

using namespace std;

string readJsonString ( string JsonString, jsmntok_t JsonStringInfo) // takes a jsmn string object and turns it into a string variable
{
	JsonString.erase( 0, JsonStringInfo.start);
	JsonString.erase( JsonStringInfo.end - JsonStringInfo.start, JsonString.size() - 1);
	return JsonString;
}

struct JsonTokenListInfo // stuff to make jsmn work
{
	int Size;
	jsmntok_t* Tokens;
};

struct JsonTokenListInfo getJsonTokenInfo( char* JsonString, int JsonTokenSize) // takes all that jsmn babble and puts it into a nice, readable structure
{
	
	jsmn_parser JsonParser;
	jsmntok_t JsonTokens[JsonTokenSize];
	jsmn_init( &JsonParser);
	jsmnerr_t JsonParserError = jsmn_parse( &JsonParser, JsonString, strlen( JsonString), JsonTokens, JsonTokenSize);
	int JsonTokenCount;
	if ( JsonParserError > JSMN_SUCCESS)
	{
		JsonTokenCount = JsonParserError;
	}
	struct JsonTokenListInfo TokenInfo;
	TokenInfo.Tokens = JsonTokens;
	TokenInfo.Size = JsonTokenCount;
	return TokenInfo;

}

int main()
{
	char* Boards = getWebPage( "http://8chan.co/boards.json");
	struct JsonTokenListInfo BoardsTokenInfo = getJsonTokenInfo( Boards, 46000);
	jsmntok_t* JsonTokens = BoardsTokenInfo.Tokens;
	int JsonTokenCount = BoardsTokenInfo.Size;
	
	string Boards_s = ( string) Boards;
	string BoardList[1000];
	int BoardCount = 0;
	int i = 0;
	for ( bool IsDone = false; IsDone == false; IsDone)
	{
		if ( i + 1 > JsonTokenCount)
		{
			IsDone = true;
		}
		else if ( JsonTokens[i].type == JSMN_STRING)
		{
			if ( readJsonString( Boards_s, JsonTokens[i]) == "uri")
			{
				if ( readJsonString( Boards_s, JsonTokens[i+1]).size() == BOARDLENGTH)
				{
					BoardList[BoardCount] = readJsonString( Boards_s, JsonTokens[i+1]);
					cout << BoardList[BoardCount] << endl;
					cout.flush();
					BoardCount++;
				}
			}
		}
		i++;
	}
	return 0;
}


