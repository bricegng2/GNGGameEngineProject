
**Note**: Most debuggers will show addresses in hexadecimal, there're shown here in decimal to make the sizes clear.

#### Code Example

Every piece of data, whether on the stack or on the heap is in RAM and will have an associated address.

```c++
int* arrayOfInts = new int[5];
for( int i=0; i<5; i++ )
	pointerToInt[i] = i;
int numIntsInArray = 5;
```

This code will allocate a block of memory 20 bytes large, enough to store 5 integer values.

If the `new` call returns the address 5000, that value will be stored in the variable `arrayOfInts`.

`arrayOfInts` is also a variable that needs to be stored in memory, in this case, it's stored on the stack. Assuming the stack starts at address 1000, it would look like this:

| Address | Value |
| ------- | ----- |
| 1000    | 5000  |
| 1020    | 5     |

While the block at 5000 would look like this:

| Address | Value |
| ------- | ----- |
| 5000    | 0     |
| 5004    | 1     |
| 5008    | 2     |
| 5012    | 3     |
| 5016    | 4     |
