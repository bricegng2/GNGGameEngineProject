Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

### Joint Types

- Revolute
	- Locked in place, but can rotate freely
- Prismatic
	- Locked to an axis, can rotate freely
- Weld
	- Welded to another body
- Distance
	- Locked at a fixed distance from another body
- Pulley
	- If one body moves up, the other moves down
- Gear
	- If one body rotates, the other rotates in the opposite dir
- Wheel
	- Spins freely and also moves up/down to simulate suspension
- Rope
	- Prevents 2 bodies from being too far apart
- Friction
	- Mean for top down games, to apply friction, can also be handled by damping values
- Motor
	- Not sure
- Mouse
	- Designed for the testbed to make a body move toward the mouse position

### Revolute Joint

Allows a body to rotate around a pivot point.

Can be used in many different ways:

- Pin
	- ![Box2D Joint - Pin](../../Images/Box2D%20Joint%20-%20Pin.png)
- Hinge
	- ![Box2D Joint - Hinge](../../Images/Box2D%20Joint%20-%20Hinge.png)
- Chain
	- ![Box2D Joint - Chain](../../Images/Box2D%20Joint%20-%20Chain.png)

#### Creating a Revolute Joint

```c++
// Declare a joint definition object
b2RevoluteJointDef jointDef;

// Select a world space anchor point
b2Vec2 anchorPos( 5, 5 );

// Initialize the joint definition with the 2 bodies and the world space anchor
jointDef.Initialize( pBodyA, pBodyB, anchorPos );

// Create the actual joint in the world
m_pWorld->CreateJoint( &jointDef );
```

Alternatively, the anchor points can be specified in local space

![Box2D Local Space Anchors](../../Images/Box2D%20Local%20Space%20Anchors.png)

```c++
// Initialize the joint definition manually
jointDef.bodyA = pBodyA;
jointDef.bodyB = pBodyB;
jointDef.localAnchorA = b2Vec2(  2, -1 );
jointDef.localAnchorB = b2Vec2( -2, -1 );
```

### Motors and Angle Limits

Many joint type can also be set up to have motors and angle limits

```c++
// Initialize the motor on the joint
jointDef.enableMotor = true;
jointDef.motorSpeed = 2; // positive values will go counter-clockwise, negative clockwise
jointDef.maxMotorTorque = 5;

// Initialize the joint’s angle limits, in radians
jointDef.enableLimit = true;
jointDef.lowerAngle = -60 * PI/180;
jointDef.upperAngle = 60 * PI/180;
```
