Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Collision Filtering

Box2D provides two separate mechanisms for filtering collisions:
- Categories/Masks
- Groups

Both can be used at the same time and each have their own strengths and weaknesses.

### Categories and Masks

Each fixture has the following properties that allow us to filter out collisions:
- Category bits
- Mask bits

Each variable is 16 bits wide which allow for 16 different categories using [Bit Flags](../../Engine/Bit%20Flags.md).

#### Categories

Up to 16 unique categories can be chosen for a fixture.
Commonly, you will mark objects as some of the following:
- Environment
- Player
- Enemy
- Bullet

This can allow players to pass through one another, or allow bullets to pass through player but not enemies, etc.

### Masks

The mask determines what the fixture with collide with.
Each fixture can be set with multiple mask bits.

for example (in binary):
```
// Flags
Player = 0000 0000 0000 0001  
Ground = 0000 0000 0000 0010

// Masks
Mask on the player = 0000 0000 0000 0011
```

i.e. Players collide with Players and Ground

### Box2D code

The code used to perform the check, from the internal Box2D source code:

```c++
uint16 catA = fixtureA.filter.categoryBits;
uint16 maskA = fixtureA.filter.maskBits;
uint16 catB = fixtureB.filter.categoryBits;
uint16 maskB = fixtureB.filter.maskBits;

if( (catA & maskB) != 0 && (catB & maskA) != 0 )
{
    // fixtures can collide
}
```

Essentially, Category A needs to be allowed to hit B and vice-versa for it to be a collision. If one category says it passes through the other, no collision will happen.

### Code

#### Define Categories

```c++
enum class PhysicsCategories
{
	PhysicsCategory_Default     = 1 << 0,
	PhysicsCategory_Environment = 1 << 1,
	PhysicsCategory_Player      = 1 << 2,
	PhysicsCategory_Enemy       = 1 << 3,
	PhysicsCategory_Purple      = 1 << 4,
	PhysicsCategory_Monkey      = 1 << 5,
	PhysicsCategory_Dishwasher  = 1 << 6,
};
```

#### Setting the Category and Mask

```c++
b2FixtureDef fixtureDef;

// Code to set up most of the fixtureDef should go here.

// This fixture is a “player” type and will collide with the environment,
//      other players and helicopters
fixtureDef.filter.categoryBits = PhysicsCategory_Player;
fixtureDef.filter.maskBits = PhysicsCategory_Environment |
                             PhysicsCategory_Player |
                             PhysicsCategory_Dishwasher;

m_pBody->CreateFixture( &fixtureDef );
```

### Groups

On top of categories and masks, Box2D also supports groups.
Groupings take priority over categories/masks.

Each fixture can be assigned a group index.
The group index is stored as an 16-bit integer (-32768 to 32767).

When 2 fixtures collide the following logic is followed:
- if fixtures are in the same “positive” group, they always collide    
- if fixtures are in the same “negative” group, they never collide    
- if fixtures are in different groups (or group 0) then categories/masks are used
