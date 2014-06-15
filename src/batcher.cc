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
#include "utils.h"
#include "status.h"

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using v8::Integer;
using v8::Local;

v8::Persistent<v8::FunctionTemplate> Batcher::constructor;

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
    Local<FunctionTemplate> tpl = NanNew<FunctionTemplate>( Batcher::New );
    tpl->SetClassName( NanNew<String>( "Batcher" ) );
    tpl->InstanceTemplate()->SetInternalFieldCount( 1 );

    NODE_SET_PROTOTYPE_METHOD( tpl, "openSocket", Batcher::OpenSocket );
    NODE_SET_PROTOTYPE_METHOD( tpl, "closeSocket", Batcher::CloseSocket );
    NODE_SET_PROTOTYPE_METHOD( tpl, "compute", Batcher::Compute );

    NanAssignPersistent( constructor, tpl );
    target->Set( NanNew<String>( "Batcher" ), tpl->GetFunction() );
}

v8::Handle<v8::Value> Batcher::NewInstance()
{
    NanScope();
    v8::Local<v8::FunctionTemplate> constructorHandle = NanNew(constructor);
    return constructorHandle->GetFunction()->NewInstance(0, NULL);
}

NAN_METHOD(Batcher::New)
{
    NanScope();

    Batcher* obj = new Batcher();
    obj->Wrap( args.This() );

    NanReturnValue(args.This());
}

NAN_METHOD(Batcher::OpenSocket)
{
    NanScope();
    Batcher* obj = node::ObjectWrap::Unwrap<Batcher>( args.This() );

    CRC32C_Status status;

    status = crc32c_init( obj->_sockets );

    if ( status == ST_SUCCESS )
    {
        NanReturnValue( NanTrue() );
    }
    else
    {
        NanThrowError( utils::GetErrorMessage( status ).c_str() );
        NanReturnUndefined();
    }
}

NAN_METHOD(Batcher::CloseSocket)
{
    NanScope();
    Batcher* obj = node::ObjectWrap::Unwrap<Batcher>( args.This() );

    CRC32C_Status status;

    status = crc32c_close( obj->_sockets );

    if ( status == ST_SUCCESS )
    {
        NanReturnValue( NanTrue() );
    }
    else
    {
        NanThrowError( utils::GetErrorMessage( status ).c_str() );
        NanReturnUndefined();
    }
}

NAN_METHOD(Batcher::Compute)
{
    NanScope();

    if( args.Length() < 1 )
    {
        NanThrowError( "Expected 1 argument" );
        NanReturnUndefined();
    }

    Batcher* obj = node::ObjectWrap::Unwrap<Batcher>( args.This() );
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
        NanThrowError( "Invalid input. Cannot compute objects. The Input has to be of String, StringObject or Buffer, Number" ) ;
        NanReturnUndefined();
    }
    else // Numbers mainly
    {
        std::string input( *String::Utf8Value( args[0] ) );
        status = crc32c_compute( obj->_sockets, input.c_str(), input.length(), &result );
    }

    if ( status == ST_SUCCESS )
    {
         NanReturnValue( NanNew<Integer>( result ) );
    }
    else
    {
        NanThrowError( utils::GetErrorMessage( status ).c_str() );
        NanReturnUndefined();
    }
}
