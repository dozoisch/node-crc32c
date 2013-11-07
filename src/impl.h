#ifndef _CRC32C_ALG
#define _CRC32C_ALG
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include <stdint.h>

/**
 * Computes a CRC32C. 
 * @param char* input The input string
 * @param uint length The length of the string
 * @param int* result The resulting checksum
 * @return int success true|false (0|1)
 */
int crc32c_compute( const char* input, const uint32_t length, uint32_t* const result );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _CRC32C_ALG
