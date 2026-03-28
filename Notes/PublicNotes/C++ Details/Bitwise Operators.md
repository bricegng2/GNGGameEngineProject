
## Bitwise AND

Uses the '&' symbol

Both bits must be true for the result to be true.
IF this AND that.

Rules:
```
0 & 0 = 0
0 & 1 = 0
1 & 0 = 0
1 & 1 = 1
```

Example:
```
  0111 1010
& 1001 0010
-----------
= 0001 0010
```

## Bitwise OR

Uses the '|' symbol

Either of the bits must be true for the result to be true.
IF this OR that.

Rules:
```
0 | 0 = 0
0 | 1 = 1
1 | 0 = 1
1 | 1 = 1
```

Example:
```
  0111 1010
| 1001 0010
-----------
= 1111 1010
```

## Bitwise NOT / Bitwise Complement

Uses the '~' symbol

Each individual bit switches state.
1's become 0's and vice-versa

Rules:
```
0 = 1
1 = 0
```

Example:
```
~ 0111 1010
-----------
= 1000 0101
```

## Bitwise XOR / Exclusive OR

Uses the '^' symbol

Either of the bits must be true for the result to be true, but not both.
IF this OR that, but not both.

Rules:
```
0 ^ 0 = 0
0 ^ 1 = 1
1 ^ 0 = 1
1 ^ 1 = 0
```

Example:
```
  0111 1010
^ 1001 0010
-----------
= 1110 1000
```

## Bitshifts

Uses the '<<' and '>>' symbols.

Moves all the bits to the left or right.
Values that go out of bounds are lost.

```
value start: 0000 0001
value << 3;
value after: 0000 1000

value start: 0110 0001
value << 2;
value after: 1000 0100

value start: 0110 0001
value >> 2;
value after: 0001 1000
```
