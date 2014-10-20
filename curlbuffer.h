#include <cstring>
#include <cstdlib>
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
	if ( CurlHandle)
	{
		curl_easy_setopt( CurlHandle, CURLOPT_URL, TargetUrl);
		curl_easy_setopt( CurlHandle, CURLOPT_FOLLOWLOCATION, true);
		curl_easy_setopt( CurlHandle, CURLOPT_WRITEFUNCTION, FillBuffer);
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
		cout << "Grab successful\n";
		char* WebPageString = WebPageOut.Buffer;
		return WebPageString;
	}
	else
	{
		cout << "ERROR: Webpage 404\n";
		return "\r\b\r";
	}
}
