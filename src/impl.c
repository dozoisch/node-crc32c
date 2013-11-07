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

#define TRUE 1 // Sucess
#define FALSE 0 // Error

int crc32c_compute( const char *input, const uint32_t length, uint32_t* const result )
{

    *result = 0x00000000;
    int sds[2] = { -1, -1 };

    struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "hash",
        .salg_name = "crc32c"
    };
	
    // Create a socket
    if( ( sds[0] = socket( AF_ALG, SOCK_SEQPACKET, 0 ) ) == -1 )
        return FALSE;
        
    if( bind( sds[0], (struct sockaddr *) &sa, sizeof(sa) ) != 0 )
        return FALSE; 
        
    if( ( sds[1] = accept( sds[0], NULL, 0 ) ) == -1 )
        return FALSE;
        
    // Send the data to be computed
    if ( send( sds[1], input, length, MSG_MORE ) != length )
        return FALSE;

    // Retrieve the result
    if( read( sds[1], result, 4 ) != 4 )
        return FALSE;
    
    return TRUE;
}

