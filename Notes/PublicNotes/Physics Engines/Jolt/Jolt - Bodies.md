Tags: #Physics #Jolt [Jolt - !Overview](Jolt%20-%20!Overview.md)

## Synchronizing Bodies

```c++
JPH::RVec3 bodyPos = pBody->GetPosition();
vec3 pos( bodyPos.GetX(), bodyPos.GetY(), bodyPos.GetZ() );

JPH::Mat44 world = pBody->GetWorldTransform().GetRotationSafe();
mat4 rm = mat4( world(0,0), world(1,0), world(2,0), world(3,0),
				world(0,1), world(1,1), world(2,1), world(3,1),
				world(0,2), world(1,2), world(2,2), world(3,2),
				world(0,3), world(1,3), world(2,3), world(3,3) );
vec3 rot = rm.GetEulerAngles();
```

## Body Properties

Jolt physics bodies have quite a few standard physics properties you can work with
- Is allowed to sleep
- Is it a sensor
- Is it dynamic, static or kinematic
- Collision groups
- User data

## Force, Impulse, Torque

Jolt bodies also use standard forces and impulses either on the bodies center of mass or on a world space coordinate.

## Shapes

The following shape types are available, among others:

- Box
- Sphere
- Capsule
- Cylinder
- Triangle
- Convex hull
- Mesh
- Heightfield
- Compound shapes
	- Instead of having multiple shapes attached to a body, Jolt takes the approach of a single compound shape having references to multiple shapes

Check the `Jolt\Physics\Collision\Shape` folder for the full list
