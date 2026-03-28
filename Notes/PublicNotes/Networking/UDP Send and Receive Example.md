Tags: #Networking 

See [IP and Sockets](IP%20and%20Sockets.md) and [Windows Sockets](Windows%20Sockets.md)

> NOTE: None of this code does proper error handling, it's just meant to show the basics.

#### Create a UDP "connectionless" socket

```c++
	socketHandle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
```

#### Bind the socket to a local address and port

This is where you would specify which network card on the computer you would want to use if there are multiple options. `INADDR_ANY` will choose the default card.

```c++
	sockaddr_in localaddr;
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = INADDR_ANY;
	localaddr.sin_port = htons( port );

	bind( socketHandle, (const sockaddr*)&localaddr, sizeof(sockaddr_in) );
```

#### Set socket send/recv calls to be non-blocking

This is a Windows specific call. Other platforms have a slightly variation of this call.
Without this call, receiving data would block until new packets arrive. This let's us check if there's any data and continue with our game if nothing is waiting for us.

```c++
	DWORD value = 1;
	ioctlsocket( socketHandle, FIONBIO, &value );
```

#### Client only: Store the server address

```c++
	hostent* host = gethostbyname( "IP ADDRESS - something like 172.0.0.1" );
	in_addr serverInAddr = *(in_addr*)host->h_addr_list[0];

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr = serverInAddr;
	serverAddr.sin_port = htons( serverPort );
```

#### Send a packet

```c++
	char bytesToSend[10];

	int flags = 0;
	sendto( socketHandle, (const char*)&bytesToSend[0], 10,
		flags, (sockaddr*)&serverAddr, sizeof(sockaddr_in) );
```

#### Receive packets

Again, normally `recvfrom` would be blocking, but we set the socket options to not block. If will return a -1 if there was no data instead of blocking.

```c++
	char buffer[1000];
	int bufferSize = 1000;
	sockaddr_in address;
	int addrLength = sizeof( sockaddr_in );

	int bytes = -500;
	while( bytes != -1 )
	{
		int flags = 0;
		bytes = (int)recvfrom( socketHandle, buffer, bufferSize,
			flags, (sockaddr*)&address, &addrLength );

		if( bytes != -1 )
		{
			// Process packets here.
		}
	}
```

If this is the server machine, we would store the address, so we can communicate back to the client that sent us data.
