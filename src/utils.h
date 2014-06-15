#ifndef _CRC32C_UTILS
#define _CRC32C_UTILS
#include <string>

#include "status.h"

namespace utils
{
std::string GetErrorMessage( const CRC32C_Status& status );
}


#endif // _CRC32C_UTILS
