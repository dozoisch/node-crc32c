#ifndef CRC32C_BATCHER
#define CRC32C_BATCHER
#include <node.h>
#include <v8.h>
#include <string>

class Batcher : public node::ObjectWrap
{

public:
    static void Init( v8::Handle<v8::Object> target );
    static v8::Handle<v8::Value> NewInstance( const v8::Arguments& args );

private: // functions
    Batcher();
    ~Batcher();

    static v8::Persistent<v8::Function> constructor;
    static v8::Handle<v8::Value> New( const v8::Arguments& args );

    /**
     * Opens a AF_ALG Socket and saves it in _sockets
     */
    static v8::Handle<v8::Value> OpenSocket( const v8::Arguments& args );

    /**
     * Close its _sockets
     */
    static v8::Handle<v8::Value> CloseSocket( const v8::Arguments& args );

    /**
     * Compute using _sockets. Takes one param which is the thing to compute
     */
    static v8::Handle<v8::Value> Compute( const v8::Arguments& args );

private: // members
    int _sockets[2];

};

#endif // CRC32C_BATCHER
