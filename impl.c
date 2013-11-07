#include "impl.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/if_alg.h>
#include <sys/param.h>
#ifdef __cplusplus
}
#endif // __cplusplus


#define uint unsigned int
#define TRUE 1
#define FALSE 0

int compute( const char *input, const uint length, int* const result )
{

    int sds[2] = { -1, -1 };

    struct sockaddr_alg sa = {
        .salg_family = AF_ALG,
        .salg_type = "hash",
        .salg_name = "crc32c"
    };

    if( ( sds[0] = socket( AF_ALG, SOCK_SEQPACKET, 0 ) ) == -1 )
        return FALSE;

    if( bind( sds[0], (struct sockaddr *) &sa, sizeof(sa) ) != 0 )
        return FALSE; 
        
    if( ( sds[1] = accept( sds[0], NULL, 0 ) ) == -1 )
        return FALSE;

    *result = 0x00000000;
    if ( send( sds[1], input, length, MSG_MORE ) != length )
        return FALSE;

    if( read( sds[1], result, 4 ) != 4 )
        return FALSE;
    
    return TRUE;
}

