#ifndef _CRC32C_ALG
#define _CRC32C_ALG
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * Computes a CRC32C. 
 * @param char* input The input string
 * @param uint length The length of the string
 * @param int* result The resulting checksum
 * @return int success true|false (0|1)
 */
int compute( const char* input, const unsigned int length, int* const result );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _CRC32C_ALG
