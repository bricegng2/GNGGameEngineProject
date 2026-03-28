
**Note**: Most debuggers will show addresses in hexadecimal, there're shown here in decimal to make the sizes clear.

#### Reference Example

References are the addresses of object managed by your compiler which cannot be changed.

```c++
int i = 5;
int& referenceToInt = i;
```

References can only be assigned on the line on which they're declared.

This code declared a single int and a single reference on the stack.

| Address | Value |
| ------- | ----- |
| 1000    | 5     |
| 1004    | 1000  |

Running this code:

```c++
referenceToInt = 9;
```

Will change the values on the stack to the following:

| Address | Value |
| ------- | ----- |
| 1000    | 9     |
| 1004    | 1000  |

The compiler will see 1000 as the value of the reference and know which block of memory to change actually change. It does this by "dereferencing" the value 1000 and changing the value at that location instead.