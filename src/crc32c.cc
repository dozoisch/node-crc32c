#include <node.h>
#include <node_buffer.h>
#include <nan.h>

#include <string>

// Check if cstdint is supported
#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
#include <cstdint>
#else // Include the old lib
#include <stdint.h>
#endif

#include "batcher.h"
#include "impl.h"

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using v8::Integer;
using v8::Local;

NAN_METHOD(Compute)
{
    NanScope();

    if( args.Length() < 1 )
    {
        NanThrowError("Expected 1 argument" );
        NanReturnUndefined();
    }
    uint32_t result;
    CRC32C_Status status;

    int sockets[2] = { -1, -1 };
    status = crc32c_init( sockets );
    if ( status == ST_SUCCESS )
    {
        if ( args[0]->IsString() || args[0]->IsStringObject() ) {
            std::string input( *String::Utf8Value( args[0] ) );
            status = crc32c_compute( sockets, input.c_str(), input.length(), &result );
        }
        else if ( node::Buffer::HasInstance( args[0] ) )
        {
            Local<Object> buf = args[0]->ToObject();
            status = crc32c_compute( sockets, node::Buffer::Data( buf ), (uint32_t) node::Buffer::Length( buf ), &result );
        }
        else if ( args[0]->IsObject() )
        {
            NanThrowError( "Invalid input. Cannot compute objects. The Input has to be of String, StringObject or Buffer, Number" );
            NanReturnUndefined();
        }
        else // Numbers mainly
        {
            std::string input( *String::Utf8Value( args[0] ) );
            status = crc32c_compute( sockets, input.c_str(), input.length(), &result );
        }
    }
    crc32c_close( sockets );

    if ( status == ST_SUCCESS )
    {
        NanReturnValue( NanNew<Integer>( result ) );
    }

    switch (status)
    {
        case ST_SOCKET_CREATE_FAILED:
            NanThrowError( "Failed to create the socket" );
            break;

        case ST_SOCKET_BIND_FAILED:
            NanThrowError( "Failed to bind the socket" );
            break;

        case ST_SOCKET_ACCEPT_FAILED:
            NanThrowError( "Socket failed to accept data" ) ;
            break;

        case ST_SOCKET_SEND_FAILED:
            NanThrowError( "Failed to send to socket" );
            break;

        case ST_SOCKET_READ_FAILED:
            NanThrowError( "Failed to read from socket" );
            break;
        default:
            NanThrowError( "Failed" );
            break;
    }

    NanReturnUndefined();
}


void Init( Handle<Object> exports )
{
    NODE_SET_METHOD( exports, "compute", Compute);
    Batcher::Init(exports);
}

NODE_MODULE( crc32c, Init )
