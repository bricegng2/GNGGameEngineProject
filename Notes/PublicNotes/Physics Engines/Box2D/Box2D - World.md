Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Box2D World

A b2World is the core of Box2D.  All physics bodies and joints exist in a world.

A Box2D world has the following properties:
- Gravity
- Allow bodies to sleep

Gravity is required when the world is created, but both of these can be changes at any time.

## Updating the World

After creating a physics world and populating it with bodies, the next step is to simulate the world. Each frame we need to update the physics simulation.

We attempt to update it at a fixed rate, say 60 times per second, regardless of the framerate. This will lead to a more stable simulation. A base timestep that we tested our game against and will generally mean less chance of surprise events like objects passing through walls if the framerate drops.

Internally, the simulation uses substeps, which can be configured. The velocity and position iterations determine how many times the velocity and position values will get adjusted internally for each step. Bigger numbers mean more accurate simulation at the cost of computation speed.

## Implementation

##### The library header

This library has a single include meant to include all the other headers commonly used by game code.

This header is called `box2d.h` and can be found in the `include/box2d` folder.

##### Create a world
```c++
b2Vec2 gravity = b2Vec2(0,-10);
m_pWorld = new b2World( gravity );
```

##### Simulation
```c++
// A timestep of deltaTime is not a good approach to running the simulation.
// We'll come back to this.
float timeStep = deltaTime;
int velocityIterations = 8;
int positionIterations = 3;

m_pWorld->Step( timeStep, velocityIterations, positionIterations );
```

##### Creating/Destroying Bodies
```c++
m_pBody = m_pWorld->CreateBody( &bodyDef );

m_pWorld->DestroyBody( m_pBody );
```

##### Destroying the World
```c++
delete m_pWorld;
```

## Additional Tips

The following advice comes from the Box2D manual:

- Keep the size of moving objects roughly between 0.1 and 10 meters
- The suggested iteration count for Box2D is 8 for velocity and 3 for position. You can tune this number to your liking, just keep in mind that this has a trade-off between speed and accuracy. Using fewer iterations increases performance but accuracy suffers
- you should use a fixed time step
- you should use a time step no larger than 1/30 seconds. A time step of 1/60 seconds will usually deliver a high quality simulation