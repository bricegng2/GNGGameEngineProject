Tags: #Networking

## Internet Protocol

There are 2 common networking protocols used on the web and in gaming (outside of LANs):
- Transmission Control Protocol (TCP)
- User Datagram Protocol (UDP)

Both are build to communicate over the Internet Protocol (IP), more specifically, most communication happens over IP version 4 or version 6. To keep this simple, the IP protocol defines the format of the data that gets transmitted between computers. This includes:
- header
	- the IP address of the host
	- the destination IP
	- extra control info:
		- version info
		- the length of the data attached
		- whether it's a TCP or a UDP packet
		- and more
- data

## Sockets

The most common method of sending the data packets if through a socket library. Sockets need to be initialized differently depending if you're setting them up for UDP or TCP.

#### UDP

UDP is the most common protocol used in games. It offers simpler setup, less overhead, but no reliability.

UDP used what are referred to as "Connectionless Sockets". These sockets can send packets to any other socket and receive packets directed towards it.

Packets are sent out without any verification if they arrived, so the application needs to decide how often to retry or how long to wait without any response before deciding that the other computer is no longer connected.

#### TCP

TCP is commonly used on the web. It has a more complicated setup process than UDP but is reliable. TCP sockets need to be connected to a single other socket and the protocol itself will expect an acknowledgement packet in response to every packet sent out. If no response is sent for a little while, the packet will be automatically resent.

This is great for the web where we want to request a page and if the packet was lost, we'll try again with the same thing a bit later. There will be a delay, but the end result is the page we requested.

This isn't great for games, since if you sent a packet saying the player is at a specific location, a quarter of a second later it'll be at a different location, so resending the old data is a waste of time.

TCP also guarantees the packets the application sent will be received in the same order.
