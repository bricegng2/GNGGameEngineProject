Tags: #Networking 

See [IP and Sockets](IP%20and%20Sockets.md) and [Windows Sockets](Windows%20Sockets.md)

> NOTE: None of this code does proper error handling, it's just meant to show the basics.

#### Initializing a Socket

```c++
    int socketHandle = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
```

#### Lookup an Address and Setup the Socket Address struct

Keep in mind, the original socket library was originally in C in 1983. The API is quite old and often not as user friendly as it could be.

```c++
    sockaddr_in serverAddress;
    in_addr ipAddress;

    struct hostent* pHost = gethostbyname( "www.google.com" );
    if( pHost )
    {
        ipAddress = *(struct in_addr*)*pHost->h_addr_list;
    }

    memset( (char*)&serverAddress, 0, sizeof(sockaddr_in) );
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons( 80 );
    serverAddress.sin_addr.s_addr = ipAddress.s_addr;
```

#### Connect

```c++
    int ret = connect( socketHandle, (sockaddr*)&serverAddress, sizeof(sockaddr) );
    if( ret != -1 )
    {
	    // We connected.
    }
```

#### Send a request

HTML requests are in plain text as are responses. So the string below is imitating a browser with a made up User-Agent code. Google might ignore this, but we could replace it with the Chrome or Firefox user agent and that would be less likely to be ignored.

```c++
	const char* requeststr = "GET http://www.google.ca/ HTTP/1.0\r\nHost: www.google.com\r\nUser-Agent: TestCode/1.0 (Win32)\r\n\r\n";
	int bytesSent = (int)send( socketHandle, requeststr, strlen(requeststr), 0 );
```

#### Receive a response

This call to recv will block until the sending responses or the socket times out. The timing of the timeout could be as long even minutes. But since TCP is reliable, if the `send` done above was lost in transmission the socket will continually retry to send until it times out or it gets an acknowledgement.

```c++
	char buffer[100001];
	int bytesreceived = (int)recv( socketHandle, buffer, 100000, 0 );
	buffer[bytesreceived] = 0;
```
