
## What is it?

Rather than have our Player move directly when input events arrive, we will create a VirtualGamepad that holds flags for the various actions the player can take.

The VirtualGamepad's job is to turn events into actions.

For example:
Our player needs to move up/down/left/right and jump
So, we create a VirtualGamepad class with 5 flags/booleans.

## Why? Abstracting Input

We do this to separate our game code from all physical devices.

We want to support as many "gamepads" as possible, so our goal is to keep all the code changes in one place.

For example, we might want to support the following:
- keyboard/mouse    
- gamepads    
- touchscreens    
- flight sticks
- steering wheels    
- motion controllers    
- adaptive controllers    
- brainwave controllers

## Abstraction Outside of the Game

The operating system or other software can do some of this for us.

For example, by supporting the XInput API, meant for xbox controllers, you can use devices that have written XInput drivers, like some logitech gamepads and a playstation controller.

Players can also use software like x360ce to remap many other controllers to work with your game.

## VirtualGamepad Event Handling

Each scene class can hold one instance of a VirtualGamepad or multiple if we have a multiplayer game.

Each Player object can hold a pointer/reference to one of the "gamepads".

When the game receives a joystick or a keyboard event, we pass it along to the VirtualGamepad instances, which set the appropriate flags.

The Player can query which flags are set in its Update method.

## Losing Focus

If our window loses focus, our VirtualGamepad might get out of sync with the physical controllers

For example:
- Joystick 'A' button was pressed => event sent => VirtualGamepad flag set    
- Player hits alt-tab to switch to another window    
- Joystick 'A' button was released => no event sent (we're not in focus)    

Solution: clear all the flags if our window loses focus

## Booleans vs. Bit Flags

The VirtualGamepad could store actions with either some booleans:

```
bool m_Up;
bool m_Down;
```

or bit flags:

```
unsigned int m_Flags; // Can store up to 32 boolean values
```

Flags can be set with the bitwise OR operator  
They can be checked with the bitwise AND operator

See [Bitwise Operators](../C++%20Details/Bitwise%20Operators.md), [Bit Flags](Bit%20Flags.md)
