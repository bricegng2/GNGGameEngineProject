Tags: #Networking 

Most socket code will run on all platforms, but a couple of things are Windows specific, like this:

To use the Windows socket (winsock) library, we need to link to it and initialize some code.

```c++
Ws2_32.lib
```

Header file:

```c++
	#include <winsock.h>
```

Initializing the winsock library.

```c++
    WSAData wsaData;
    WSAStartup( MAKEWORD(1, 1), &wsaData );
```

Setting socket options are also platform specific, so you'll see the following in [TCP Web Request Example](TCP%20Web%20Request%20Example.md).

```c++
	DWORD value = 1;
	ioctlsocket( socketHandle, FIONBIO, &value );
```
