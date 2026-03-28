
See [Bitwise Operators](../C++%20Details/Bitwise%20Operators.md)

## What are bit flags?

Bit flags refers to the idea of using each individual bit in a variable as a boolean.

3 common datatypes are char, short and int. These are 8-bit, 16-bit and 32-bit respectively. Which means they can hold a bool value for each bit.

Using a char for example, we could say each bit represents a different property. For example if we wanted to track which objectives have been completed in a game:

| Bit Flag | Decimal Number | Meaning |
| ---- | ---- | ---- |
| 0000 0001 | 1 | Opened Drawer |
| 0000 0010 | 2 | Read Note |
| 0000 0100 | 4 | Picked Up Rock |
| 0000 1000 | 8 | Broke Fence |
| 0001 0000 | 16 | Talked To Neighbour |
| 0010 0000 | 32 | Turned On Light |
| 0100 0000 | 64 | Unused |
| 1000 0000 | 128 | Unused |

This would allow us to track the state of the game with 1 char (if there are less than 8 states)

## Using bit flags

#### Defining bit flags

There are a few ways to define bit flags, and it doesn't really matter in the end, but using a combination of bitshifts with enums works well:

```c++
enum GameState
{
	OpenedDrawer  = 1 << 0,
	ReadNote      = 1 << 1,
	PickedUpRock  = 1 << 2,
	BrokeFence    = 1 << 3,
	Talked        = 1 << 4,
	TurnedOnLight = 1 << 5,
};
```

This will produce the bit patterns from the table above.

This isn't using an `enum class` to avoid typecasts, but be careful of the scope if you choose not to use an `enum class`.

#### Setting a single flag

```c++
int flags = 0; // No flags are set.

// Set the 4th bit.
if( Event->Type() == "Broke the fence" )
{
	flags |= GameState::BrokeFence;
}
```

#### Checking if a flag is set

```c++
int flags = GameState::OpenedDrawer | GameState::BrokeFence;

if( flag & GameState::BrokeFence )
{
	// The fence if broken.
}
```

#### Unsetting a flag

```c++
int flags = GameState::OpenedDrawer | GameState::BrokeFence;

// Unset the 4th bit.
if( Event->Type() == "Fixed the fence" )
{
	flags &= ~GameState::BrokeFence; // Fence is no longer broken.
}
```

#### Flipping a flag

```c++
// Flip the 6th bit.
if( Event->Type() == "Interected with light switch" )
{
	// If the light was on, it's now off and vice versa
	flags ^= GameState::TurnedOnLight;
}
```
