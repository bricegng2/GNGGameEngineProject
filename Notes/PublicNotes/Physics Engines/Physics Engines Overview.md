
## Overview

Physics Engines generally comprise of the following

- Worlds
- Bodies
	- Static
	- Dynamic
	- Kinematic
	- Sensors
- Shapes
	- Circles/Spheres
	- Boxes/Cubes
	- Capsules
	- Meshes
	- etc
- Constraints a.k.a. Joints
	- Types
		- Weld/Fixed
		- Distance
		- Revolute/Hinge
		- Prismatic/Slider
		- etc
	- Properties
		- Limits
		- Motors
- Processes
	- Simulation
	- Collision Detection
	- Collision Filtering

## Worlds

Physics engines keep track of an entire world of physics bodies, this is completely separate from our scene objects, which are mainly used for rendering.

Physics worlds don't have a graphical representation of their own, they're purely collections of objects with positional information for each body in the world.

That means that each frame we need to sync our graphics objects to those in the physics world.

## Bodies

Bodies store position, velocity, and other physics properties, and have a reference to a shape.

## Shapes

This are often a mix of simple mathematically derived shapes, like circles, squares and capsules. and more complex, like convex hulls and triangle meshes.

Checking for collisions between the simple shapes types is generally fast. For example a pit willed with circles or spheres might require a lot of objects to check for collisions with each other, but the collision checks are fast, generally just a distance check. There are similar optimizations that can be made for capsules (which can be treated as circle-sweeps) and rectangles/boxes (look up Separated Axis Theorem for more detail).

Collisions with mesh shapes involves checking for collisions against every triangle in the mesh, this is a very expensive operation and should be avoided where possible. Some physics engines don't allow for mesh/mesh collision checks, but will check mesh collisions with the simpler primitive shapes.

## Constraints

Constraints are as named, a method of constraining the movement of bodies in some way.

This could involve:
- preventing rotation
- preventing movement
- limiting movement to a single axis
- attaching bodies to each other
