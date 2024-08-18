#include "socket-wrapper.h"

std::ostream& operator<<(std::ostream& out, const SocketWrapper& sock)
{
    sock.print(out);
    return out;
}