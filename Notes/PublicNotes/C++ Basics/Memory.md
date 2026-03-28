
#### Random Access Memory (RAM)

A computer with 8 gigs of RAM can store 8 billion bytes in memory. This doesn't prevent the code or the operating system from storing some of this to a drive (hdd or ssd) and loading different things on the fly.

You'll hear a lot about stack and heap memory, but both are stored in main RAM and there's no physical difference between the two.

The difference between stack and heap is whether or not the application reserved the memory when it launched or if the user code allocated it while the app was running.

#### Stack

This block of memory is allocated immediately upon launch of your game, the size of the block allocated is decided by the compiler settings. It might default to a value of about 1 megabyte.

Stacks are often thought of as a "stack" of things, with new things being "pushed" on top of the stack and being "popped" off of the stack when we're done with them. In reality, stacks can be thought of as a vector growing as you add items and shrinking as you release them, each subsequent item will fit at the next available address.

Locally defined variables (and function arguments) are added to the stack when they are defined.

For example, if we have a stack in RAM starting at address 0x1000 and it's completely empty, the following code:

```c++
int a = 10;
int b = 20;
int c = 30;
```

Would result in a stack that look like this: (for reference an int is 4 bytes large)

| Address | Value |
| ------- | ----- |
| 0x1000  | 10    |
| 0x1004  | 20    |
| 0x1008  | 30    |
Variables will get cleared from the stack automatically when the current scope ends. i.e. When you exit a function or more generally when you hit a "}"
#### Heap

The heap is again, just RAM. It is controlled by your operating system (just like the stack).
Whenever you want to store something you can ask the operating system for a chunk of RAM.

```c++
int* addressOfInt = new int();
Shape* addressOfShape = new Shape();
```

The compiler needs to know how large an object is in order for the "new" call to work.

```c++
class Shape
{
	float radius; // 4 bytes.
	float x; // 4 bytes.
	float y; // 4 bytes.
}
```

Shape is 12 bytes large (regardless of methods inside the class). For completeness if there are any virtual methods in a class, there's also a pointer to a list of the address of those functions, adding another 8 bytes (in 64 bit mode).

Calling `Shape* addressOfShape = new Shape();` will generate code that will ask the operating system for a block of memory 12 bytes large.

See [Pointers](Pointers.md)
See [References](References.md)
See [Memory Allocation Tracking](../C++%20General/Memory%20Allocation%20Tracking.md)
