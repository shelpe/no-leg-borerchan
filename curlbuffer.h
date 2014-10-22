#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <curl/curl.h>

using namespace std;

struct BufferStruct // stuff that makes curl work
{
	char* Buffer;
	size_t Size;
};

static size_t FillBuffer( void* DataPointer, size_t Size, size_t NumMemb, void* Data) // stuff that makes curl work
{
	size_t RealSize = Size * NumMemb;
	struct BufferStruct* Memory = ( struct BufferStruct*) Data;

	Memory->Buffer = ( char*) realloc( Memory->Buffer, Memory->Size + RealSize + 1);

	if ( Memory->Buffer)
	{
		memcpy( &( Memory->Buffer[Memory->Size]), DataPointer, RealSize);
		Memory->Size += RealSize;
		Memory->Buffer[Memory->Size] = 0;
	}
	return RealSize;
}


char* getWebPage( char* TargetUrl) // returns a whole webpage in a char array in memory
{
	curl_global_init( CURL_GLOBAL_DEFAULT);
	CURL* CurlHandle = curl_easy_init();
	struct BufferStruct WebPageOut;
	WebPageOut.Buffer = NULL;
	WebPageOut.Size = 0;
	srand( time(NULL));
	
	fstream RefererFile;
	char* RefererFile_Buffer[3];
	RefererFile.open( "referers.txt", fstream::in);
	if ( RefererFile.is_open() == 0)
	{
		return "no_referers";
	}
	string RefererList[256];
	string Referer;
	int RefererCount;
	for ( RefererCount = 0; getline( RefererFile, Referer); RefererCount++)
	{
		RefererList[RefererCount] = Referer;
	}
	RefererFile.close();

	fstream UserAgentFile;
	char* UserAgentFile_Buffer[3];
	UserAgentFile.open( "useragents.txt", fstream::in);
	if ( UserAgentFile.is_open() == 0)
	{
		return "no_useragents";
	}
	string UserAgentList[256];
	string UserAgent;
	int UserAgentCount;
	for ( UserAgentCount = 0; getline( UserAgentFile, UserAgent); UserAgentCount++)
	{
		UserAgentList[UserAgentCount] = UserAgent;
	}
	UserAgentFile.close();
	cout << RefererList[rand() % RefererCount] << " " << UserAgentList[rand() % UserAgentCount] << endl;

	if ( CurlHandle)
	{
		curl_easy_setopt( CurlHandle, CURLOPT_URL, TargetUrl);
		curl_easy_setopt( CurlHandle, CURLOPT_FOLLOWLOCATION, true);
		curl_easy_setopt( CurlHandle, CURLOPT_WRITEFUNCTION, FillBuffer);
		curl_easy_setopt( CurlHandle, CURLOPT_REFERER, RefererList[rand() % RefererCount].c_str());
		curl_easy_setopt( CurlHandle, CURLOPT_USERAGENT, UserAgentList[rand() % UserAgentCount].c_str());
		curl_easy_setopt( CurlHandle, CURLOPT_WRITEDATA, ( void*) &WebPageOut);
		CURLcode CurlError = curl_easy_perform( CurlHandle);
		if ( CurlError != 0)
		{
			cerr << curl_easy_strerror( CurlError) << endl;
		}
		curl_easy_cleanup( CurlHandle);
	}
	curl_global_cleanup();
	char* WebPageString;
	if ( WebPageOut.Size)
	{
		char* WebPageString = WebPageOut.Buffer;
		return WebPageString;
	}
	else
	{
		return "\r\b\r";
	}
}
