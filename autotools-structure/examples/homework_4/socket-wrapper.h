#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H

#include <string>

class SocketWrapper {

public:

    /**
	 * Virtual destructor.
	 */
    virtual ~SocketWrapper() {};
    
    /**
     * Receives data from remote host.
     */
	virtual int recvData(char* buf) = 0;

    /**
     * Send data to remote host.
     */
	virtual int sendData(const char* buf, size_t size_to_tx) = 0;

    /**
    * Function executed in a thread dispatched by the constructor 
    * to start the server listener
    */
    virtual void runServer() = 0;

protected:

    /**
	 * Print relevant information to a stream
	 * @param out an std::stream
	 */
	virtual void print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out, const SocketWrapper& sock);

};

/**
 * Overleaded stream operator
 */
std::ostream& operator<<(std::ostream& out, const SocketWrapper& sock);

#endif // SOCKET_WRAPPER_H