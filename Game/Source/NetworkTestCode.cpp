#include "Framework.h"
#include "NetworkTestCode.h"
#include <winsock.h>

void runNetworkTestCode()
{
    WSAData wsaData;
    WSAStartup(MAKEWORD(1, 1), &wsaData);

    int socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in serverAddress;
    in_addr ipAddress;

    struct hostent* pHost = gethostbyname("www.google.com");
    if (pHost)
    {
        ipAddress = *(struct in_addr*)*pHost->h_addr_list;
    }

    memset((char*)&serverAddress, 0, sizeof(sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(80);
    serverAddress.sin_addr.s_addr = ipAddress.s_addr;

    int ret = connect(socketHandle, (sockaddr*)&serverAddress, sizeof(sockaddr));
    if (ret != -1)
    {
        const char* requeststr = "GET http://www.google.ca/ HTTP/1.0\r\nHost: www.google.com\r\nUser-Agent: TestCode/1.0 (Win32)\r\n\r\n";
        int bytesSent = (int)send(socketHandle, requeststr, strlen(requeststr), 0);
    }
}