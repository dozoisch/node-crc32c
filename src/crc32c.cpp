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
	bool success;
	if(args[0]->IsObject())
	{
		char* input = node::Buffer::Data(args[0]->ToObject());
		uint32_t length = node::Buffer::Length(args[0]->ToObject());
		success = crc32c_compute( input, length, &result );
	}
	else
	{
		std::string input(*String::Utf8Value(args[0]));
		success = crc32c_compute( input.c_str(), input.length(), &result );
	}

	if( !success )
	{
		ThrowException( Exception::TypeError( String::New( "Failed to compute the checksum" ) ) );
		return scope.Close( Undefined() );
	}

	std::stringstream ss;
	ss << std::hex << result;
	return scope.Close( String::New( ss.str().c_str() ) );
}

void Init( Handle<Object> exports )
{
	exports->Set( String::NewSymbol( "compute" ),
		FunctionTemplate::New( Compute )->GetFunction() );
}

NODE_MODULE( crc32c, Init )
