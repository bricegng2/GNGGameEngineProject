Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Units

Physics libraries, including Box2D, generally recommend using real world units for your objects. i.e. meters for lengths/distances, kg for mass, seconds for time, etc.

This helps us create a world that's consistent without resorting to magic numbers.

## Math Units

Newton's second law of motion: **F = ma**    (Force = mass * acceleration)

The standard unit of force is a Newton (N)      **N = 1kg ⋅ 1m/(s^2)**

A Newton is the amount of force required to make an 1kg object accelerate to a velocity of 1m/s in 1 second

i.e. if we want a 1kg body to reach a velocity of 1m/s (ignoring friction), we can:
- apply a force of 1 newton for 1 full second    
- or apply a force of 60 Newtons for 1/60th of a second

## Moving Bodies at a Fixed Velocity

We can use that knowledge to make a body move at a fixed velocity.

If our player is standing still and we want it to instantly have a velocity of 2m/s to the right.

We can:
- Find the mass of the player body    
- Find the current velocity of the player    
- Apply a force large enough to reach that velocity

The code could look something like this, in 1D:

```c++
float mass = m_pBody->GetMass();
float currentVelocity = m_pBody->GetLinearVelocity();
float targetVelocity = 2.0f;
float velocityDiff = targetVelocity - currentVelocity;

float timeStep = 1/60.0f;
m_pBody->ApplyForce( mass * velocityDiff / timeStep );
```

or, since impulses are instant forces in Newtons, not affected by timeStep

```c++
m_pBody->ApplyImpulse( mass * velocityDiff );
```

## Next Steps

Getting the player to move at the velocity we want is just the start.

The following and more should be considered, depending on your game:
- Should the player accelerate when it starts moving    
- Should the player decelerate when stopping or "skid" when changing direction    
- How will external forces affect the player (i.e. getting hit by a truck)
