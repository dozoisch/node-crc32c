#include "batcher.h"
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

namespace
{
Local<String> GetErrorMessage( const CRC32C_Status& status )
{
    switch (status)
    {
        case ST_SOCKET_CREATE_FAILED:
            return String::New( "Failed to create the socket" );
        case ST_SOCKET_BIND_FAILED:
            return String::New( "Failed to bind the socket" );
        case ST_SOCKET_ACCEPT_FAILED:
            return String::New( "Socket failed to accept data" ) ;
        case ST_SOCKET_SEND_FAILED:
            return String::New( "Failed to send to socket" );
        case ST_SOCKET_READ_FAILED:
            return String::New( "Failed to read from socket" );
        default:
            return String::New( "Failed" );
    }
}
} // end anonymous

Persistent<Function> Batcher::constructor;

Batcher::Batcher()
{
    _sockets[0] = -1;
    _sockets[1] = -1;
}

Batcher::~Batcher()
{
}

void Batcher::Init( Handle<Object> target )
{
    Local<FunctionTemplate> tpl = FunctionTemplate::New( New );

    tpl->SetClassName( String::NewSymbol( "Batcher" ) );
    tpl->InstanceTemplate()->SetInternalFieldCount( 1 );

    tpl->PrototypeTemplate()->Set( String::NewSymbol( "openSocket" ),
        FunctionTemplate::New( OpenSocket )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "closeSocket" ),
        FunctionTemplate::New( CloseSocket )->GetFunction() );
    tpl->PrototypeTemplate()->Set( String::NewSymbol( "compute" ),
        FunctionTemplate::New( Compute )->GetFunction() );

    constructor = Persistent<Function>::New( tpl->GetFunction() );
    target->Set( String::NewSymbol( "Batcher" ), constructor );
}

Handle<Value> Batcher::New( const Arguments& args )
{
    HandleScope scope;

    Batcher* obj = new Batcher();
    obj->Wrap( args.This() );

    return args.This();
}

Handle<Value> Batcher::OpenSocket( const Arguments& args )
{
    HandleScope scope;
    Batcher* obj = ObjectWrap::Unwrap<Batcher>( args.This() );

    CRC32C_Status status;

    status = crc32c_init( obj->_sockets );

    if ( status == ST_SUCCESS )
    {
        return scope.Close( Boolean::New( true ) );
    }
    else
    {
        ThrowException( Exception::Error( GetErrorMessage( status ) ) );
        return scope.Close( Undefined() );
    }
}

Handle<Value> Batcher::CloseSocket( const Arguments& args )
{
    HandleScope scope;
    Batcher* obj = ObjectWrap::Unwrap<Batcher>( args.This() );

    CRC32C_Status status;

    status = crc32c_close( obj->_sockets );

    if ( status == ST_SUCCESS )
    {
        return scope.Close( Boolean::New( true ) );
    }
    else
    {
        ThrowException( Exception::Error( GetErrorMessage( status ) ) );
        return scope.Close( Undefined() );
    }
}

Handle<Value> Batcher::Compute( const Arguments& args )
{
    HandleScope scope;

    if( args.Length() < 1 )
    {
        ThrowException( Exception::TypeError( String::New( "Expected 1 argument" ) ) );
        return scope.Close( Undefined() );
    }

    Batcher* obj = ObjectWrap::Unwrap<Batcher>( args.This() );
    CRC32C_Status status;
    uint32_t result = 0x00000000;

    if ( args[0]->IsString() || args[0]->IsStringObject() ) {
        std::string input( *String::Utf8Value( args[0] ) );
        status = crc32c_compute( obj->_sockets, input.c_str(), input.length(), &result );
    }
    else if ( node::Buffer::HasInstance( args[0] ) )
    {
        Local<Object> buf = args[0]->ToObject();
        status = crc32c_compute( obj->_sockets, node::Buffer::Data( buf ), (uint32_t) node::Buffer::Length( buf ), &result );
    }
    else if ( args[0]->IsObject() )
    {
        ThrowException( Exception::Error ( String::New( "Invalid input. Cannot compute objects. The Input has to be of String, StringObject or Buffer, Number" ) ) );
        return scope.Close( Undefined() );
    }
    else // Numbers mainly
    {
        std::string input( *String::Utf8Value( args[0] ) );
        status = crc32c_compute( obj->_sockets, input.c_str(), input.length(), &result );
    }

    if ( status == ST_SUCCESS )
    {
         return scope.Close( Integer::NewFromUnsigned( result ) );
    }
    else
    {
        ThrowException( Exception::Error( GetErrorMessage( status ) ) );
        return scope.Close( Undefined() );
    }
}
