Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Movement through Forces

There are 4 different ways to move objects in Box2D using physics

- Forces    
- Torques    
- Linear Impulses    
- Angular Impulses

There are also more ways that bypass the physics simulation
- Manually changing position, velocity, angular velocity, etc...

#### Forces vs Impulses

Forces:
- used for applying continuous forces    
- force will be scaled by how much time passed    
- must be applied each frame
- examples:
	- gravity, car/jet engines, thrusters    

Impulses:
- applied instantly, will change a body’s velocity immediately    
- examples:
	- jumping, striking a ball in pool, firing a bullet

#### Applying Force

When applying a force on an object, you have to select a location to apply the force to.
If the force is applied anywhere other than the center of mass, torque will be created on the body.

![Box2D Torque](../../Images/Box2D%20Torque.png)

#### Forces in World Space

In Box2d, linear forces are applied to points in world space.

So, when calling ApplyForce or ApplyLinearImpulse, you need to provide a point in world space to apply the force to.

For example, to apply the force to the center of the body, call:
```c++
m_pBody->ApplyForce( dir, m_pBody->GetWorldCenter(), true );
```

To apply the force near the top left of the body, call:
```c++
m_pBody->ApplyForce( dir, m_pBody->GetWorldPoint( b2Vec2(-1,1) ), true );
```
