Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Physics Bodies

A physics body contains all the characteristics of the body other than its size and shape, including:
- type: static, dynamic, kinematic
- position: where the body is in the world
- rotation: the angle of the body
- velocity: the direction and speed of movement of the body
- angular velocity: the direction and speed of the rotation of the body

To add a body to a Box2D world, we use the following world function:
- b2Body* b2World::CreateBody(const b2BodyDef* def)

## Body Definitions

A body definition object must be defined in order to create a body.

The b2BodyDef holds the following, among other things:
- type: static, dynamic, kinematic
- position
- angle: in radians
- user data: a pointer to user defined data

The user data pointer can be as simple as a pointer to the game object associated with the physics body or a structure that contains more data about the body.

It will be used later on when dealing with collisions.

## Body Types

Bodies can come in 3 types:
- static
- dynamic
- kinematic

#### Kinematic Bodies

The 3rd type, Kinematic, is a mix of static and dynamic
It’s static in the sense that no forces can affect it
It’s dynamic in the sense that it can move

Kinematic bodies have the following properties
- they can move
- they can rotate
- they only collide with dynamic bodies
- they always push dynamic bodies away from them
- forces have no effect on them
- the only way to move them is to set their linear/angular velocity directly

## Implementation

##### Create a body
When creating a body, rather than passing in 13 different parameters, the box2d library uses a pattern of making local "definition" objects
In this case a `b2BodyDef` is simply a struct with 13 public members
```c++
// Initialize a body definition object
b2BodyDef bodyDef;

// Set other b2BodyDef members here.
// position, angle, type, etc

// Create the body.
m_pBody = m_pWorld->CreateBody( &bodyDef );
```

Bodies need fixtures and shapes before they can be affected by physics

##### Create a shape
Box2D physics shapes need to be convex
There's a helper function to make a box, but look at its implementation to see how other shapes could be made, such as a hexagon
There's also a `b2CircleShape` which is a special case for circles and is very useful
```c++
b2PolygonShape boxShape;
boxShape.SetAsBox( 1, 1 );
```

##### Create a fixture
A fixture holds a shape along with other properties like density
In 3D physics engines, shapes often have many more vertices, so sharing "physics meshes" between physics bodies with different properties (density, bounciness, etc) is common. That's why we have this pattern of a *Body* holding multiple *fixtures*, each referencing a *shape/physics mesh*
```c++
b2FixtureDef fixtureDef;
fixtureDef.shape = &boxShape;
// Set other b2FixtureDef members here.

m_pBody->CreateFixture( &fixtureDef );
```

## Fixed Rotation

Amongst many other options, a physics body can be set to not rotate, this can be useful for player/enemy objects

```c++
m_pBody->SetFixedRotation( true );
```

Keep in mind, by doing this, you're still able to give your sprite a z-rotation even if it doesn't line up with the physics object