#ifndef CRC32C_BATCHER
#define CRC32C_BATCHER
#include <node.h>
#include <nan.h>
#include <string>

class Batcher : public node::ObjectWrap
{

public:
    static void Init( v8::Handle<v8::Object> );
    static v8::Handle<v8::Value> NewInstance();

private: // functions
    Batcher();
    ~Batcher();

    static v8::Persistent<v8::FunctionTemplate> constructor;
    static NAN_METHOD(New);

    /**
     * Opens a AF_ALG Socket and saves it in _sockets
     */
    static NAN_METHOD(OpenSocket);

    /**
     * Close its _sockets
     */
    static NAN_METHOD(CloseSocket);

    /**
     * Compute using _sockets. Takes one param which is the thing to compute
     */
    static NAN_METHOD(Compute);

private: // members
    int _sockets[2];

};

#endif // CRC32C_BATCHER
