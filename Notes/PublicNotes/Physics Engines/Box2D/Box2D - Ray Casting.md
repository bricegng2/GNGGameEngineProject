Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

Raycasting simply means testing if a straight line (a ray) intersects with an object
- Used when firing a gun that instantly hits an object    
- Used to check for obstacles between an enemy and a player    
- etc.

In Box2D, there are 2 different ways to raycast
- Raycast against an individual fixture    
- Raycast against all fixtures in the world

### Example Raycasting against a Fixture

- Inputs in red, outputs in orange
![Box2D - Raycast Fixture](../../Images/Box2D%20-%20Raycast%20Fixture.png)

The b2Fixture class has the following method for raycasting:
```c++
RayCast(b2RayCastOutput* output, b2RayCastInput& input, int32 childIndex)
```

The b2RayCastInput structure consists of the following:
- 2 points: the direction of the ray    
- maximum fraction: a % along the ray, can be greater than 1 to make ray longer    

The b2RayCastOutput structure consists of the following:
- normal: the direction the face we collided with is pointing    
- fraction: how far along our ray we colliding with the fixture    

The childIndex is used for chain shapes, it picks which edge to test against.

### Example Raycasting against the World

- Inputs in red, outputs in orange
![Box2D - Raycast World](../../Images/Box2D%20-%20Raycast%20World.png)

A subclass of b2RayCastCallback needs to be created.  
The following function needs an override:
```c++
virtual float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point,
                              const b2Vec2& normal, float32 fraction ) = 0;
```

The `ReportFixture()` method will get called for each fixture that intersects the ray
- The order the fixtures are found isn’t related to their positions
- They can be reported in any order, not from nearest to furthest

#### Return Values

ReportFixture will get called for each fixture the ray intersects

When called, you can control what happens next with the following return values:
- returning -1: will ignore this fixture and continue finding other fixtures  
- returning 0: will stop the ray cast, ignoring other fixtures  
- returning fraction: will clip the ray at this % and continue  
- returning 1: will continue finding fixtures

3 General rules can be made from the previous info:
- If you want to make a list of all fixtures hit by the ray, return 1
	- This will continue to return fixtures until all intersections are reported    
	- Store all fixtures
- If you want to find the closest, return fraction
	- This will cause future calls to ReportFixture to be made with a shortened ray    
	- Store the last fixture reported
- If you just want to check for any collision, return 0
	- This will stop Box2D from checking for more fixtures

#### Example: Check if Anything is Intersecting the Ray
```c++
class RayCastResultCallback : public b2RayCastCallback
{
	bool m_HitSomething = false;
	RayCastResultCallback() {}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
				const b2Vec2& normal, float32 fraction) override
	{
		m_HitSomething = true;
		return 0; // Stop searching
	}
};
```

```c++
RayCastResultCallback raycastResult;

b2Vec2 pointA = b2Vec2( 0, 0 );
b2Vec2 pointB = b2Vec2( 0, 10 );

pWorld->RayCast( &raycastResult, pointA, pointB );

if( raycastResult.m_HitSomething == true )
{
    // do stuff
}
```

#### Example: Finding the Nearest Body Along the Ray

```c++
class RayCastResultCallback : public b2RayCastCallback
{
public:
	bool m_Hit = false;
	b2Body* m_pBody = nullptr;

public:
	RayCastResultCallback() {}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction) override
	{
		m_Hit = true;
		m_pBody = fixture->GetBody();
		
		return fraction; // Continue search, we’ll only store the closest Body
	}
};
```
