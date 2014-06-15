#include "impl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_alg.h>
#include <sys/param.h>
#ifdef __cplusplus
}
#endif // __cplusplus

CRC32C_Status crc32c_init( int sockets[2] )
{
    struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "hash",
        .salg_name = "crc32c"
    };

    // Create a socket
    if( ( sockets[0] = socket( AF_ALG, SOCK_SEQPACKET, 0 ) ) == -1 )
        return ST_SOCKET_CREATE_FAILED;

    if( bind( sockets[0], (struct sockaddr *) &sa, sizeof(sa) ) == -1 )
        return ST_SOCKET_BIND_FAILED;

    if( ( sockets[1] = accept( sockets[0], NULL, 0 ) ) == -1 )
        return ST_SOCKET_ACCEPT_FAILED;

    return ST_SUCCESS;
}

CRC32C_Status crc32c_compute( const int sockets[2], const char *input, const uint32_t length, uint32_t* const result )
{
    // Send the data to be computed
    if ( send( sockets[1], input, length, MSG_MORE ) != length )
        return ST_SOCKET_SEND_FAILED;

    // Retrieve the result
    if( read( sockets[1], result, 4 ) != 4 )
        return ST_SOCKET_READ_FAILED;

    return ST_SUCCESS;
}

CRC32C_Status crc32c_close( int sockets[2] )
{
    close( sockets[0] );
    sockets[0] = -1;
    close( sockets[1] );
    sockets[1] = -1;
    return ST_SUCCESS;
}
