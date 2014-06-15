#include "utils.h"

#include <cerrno>
#include <cstring>
#include <sstream>

std::string utils::GetErrorMessage( const CRC32C_Status& status )
{
    std::stringstream ss;
    switch (status)
    {
        case ST_SOCKET_CREATE_FAILED:
            ss << "Failed to create the socket with ERRNO: ";
            break;
        case ST_SOCKET_BIND_FAILED:
            ss << "Failed to bind the socket";
            break;
        case ST_SOCKET_ACCEPT_FAILED:
            ss << "Socket failed to accept data" ;
        case ST_SOCKET_SEND_FAILED:
            ss << "Failed to send to socket";
        case ST_SOCKET_READ_FAILED:
            ss << "Failed to read from socket";
        default:
            return "Failed";
    }

    ss << errno << std::endl << strerror(errno);
    return ss.str();
}
