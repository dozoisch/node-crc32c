#ifndef _CRC32C_ALG
#define _CRC32C_ALG
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdint.h>
#include "status.h"


/**
 * Creates a socket for the checksum
 * @param int[2] the two identifiers of the socket created
 * @return CRC32C_Status Enum of the success/error
 */
CRC32C_Status crc32c_init( int sockets[2] );

/**
 * Computes a CRC32C.
 * @param int[2] the two identifiers of the socket to use
 * @param char* input The input string
 * @param uint length The length of the string
 * @param int* result The resulting checksum
 * @return CRC32C_Status Enum of the success/error
 */
CRC32C_Status crc32c_compute( const int sockets[2], const char* input, const uint32_t length, uint32_t* const result );

/**
 * Closes sockets
 * @param int[2] the two identifiers of the socket to close
 */
CRC32C_Status crc32c_close( int sockets[2] );


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _CRC32C_ALG
