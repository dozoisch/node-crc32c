#include <node.h>
#include <v8.h>
#include <node_buffer.h>

#include <string>
#include <sstream>

// Check if cstdint is supported
#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
#include <cstdint>
#else // Include the old lib
#include <stdint.h>
#endif

#include "impl.h"

using namespace v8;


Handle<Value> Compute( const Arguments& args )
{
	HandleScope scope;

	if( args.Length() < 1 )
	{
		ThrowException( Exception::TypeError( String::New( "Expected 1 argument" ) ) );
		return scope.Close( Undefined() );
	}
	uint32_t result;
	CRC32C_Status status;

	int sockets[2] = { -1, -1 };
	status = crc32c_init( sockets );
	if ( status == ST_SUCCESS )
	{
		result = 0x00000000;
		std::string input(*String::Utf8Value(args[0]));
		status = crc32c_compute( sockets, input.c_str(), input.length(), &result );
	}
	crc32c_close( sockets );

	switch (status)
	{
		case ST_SUCCESS:
		{
			std::stringstream ss;
			ss << std::hex << result;
			return scope.Close( String::New( ss.str().c_str() ) );
		}
		case ST_SOCKET_CREATE_FAILED:
			ThrowException( Exception::Error( String::New( "Failed to create the socket ")));
			break;

		case ST_SOCKET_BIND_FAILED:
			ThrowException( Exception::Error( String::New( "Failed to bind the socket ")));
			break;

		case ST_SOCKET_ACCEPT_FAILED:
			ThrowException( Exception::Error( String::New( "Socket failed to accept data ")));
			break;

		case ST_SOCKET_SEND_FAILED:
			ThrowException( Exception::Error( String::New( "Failed to send to socket")));
			break;

		case ST_SOCKET_READ_FAILED:
			ThrowException( Exception::Error( String::New( "Failed to read from socket")));
			break;
	}

	return scope.Close( Undefined() );
}

void Init( Handle<Object> exports )
{
	exports->Set( String::NewSymbol( "compute" ),
		FunctionTemplate::New( Compute )->GetFunction() );
}

NODE_MODULE( crc32c, Init )
