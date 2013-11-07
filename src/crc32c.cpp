#include <node.h>
#include <v8.h>

#include <string>
#include <sstream>

using namespace v8;

#include "impl.h"

Handle<Value> Compute( const Arguments& args )
{
	HandleScope scope;
	
	if( args.Length() < 1 )
	{
		ThrowException( Exception::TypeError( String::New( "Expected 1 argument" ) ) );
		return scope.Close( Undefined() );
	}
	
	std::string input(*v8::String::Utf8Value(args[0]));
	
	int result;
	bool success = compute( input.c_str(), input.length(), &result );
	
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
