Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Contact Normals

When two fixtures collide, Box2D provides a b2Contact that contains a b2Manifold.

The b2Manifold contains a local space information about the contact, including:
- type: depends on shapes colliding (circle/circle, circle/polygon, polygon/polygon)
- local normal: direction it points is different based on type
	- if two circles collide, normal is (0,0)
	- if two polygons collide, normal can be pointing from A->B or B->A depending on type
	- if a circle and a polygon collide, normal can be pointing from A->B or B->A depending on type

#### World Manifold

A world manifold can be created by the b2Contact.
With the world manifold, we don’t need to worry about the type of contact.
This normal is always in world space and points from Fixture A to Fixture B.

![Box2D World Manifold](../../Images/Box2D%20World%20Manifold.png)

#### Normal Direction

When telling the GameObject the direction it got hit, we likely want to flip the direction of the normal so it points toward the object it hit.

For example: Object A fell down and landed on Object B

![Box2D Collision Normal](../../Images/Box2D%20Collision%20Normal.png)

Object A’s World Collision Normal: ( 0, -1 )
Object B’s World Collision Normal: ( 0, 1 )
- we flip the normal to tell Object B it got hit from above

#### Code

```c++
b2WorldManifold manifold;
contact->GetWorldManifold( &manifold );
  
vec2 normal( manifold.normal.x, manifold.normal.y );
  
CollisionNormalA = normal;
CollisionNormalB = normal * -1;
```

#### Note about Sensors

While sensors don't collide with anything they still give ContactListener callbacks (BeginContact, EndContact, etc...).

A contact manifold will not be available for collisions with sensors, so you don't get a contact normal.
