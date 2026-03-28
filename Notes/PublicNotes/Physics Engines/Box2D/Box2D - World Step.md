Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Framerate Independence

Ideally we want our physics simulation to run at a fixed timestep, this ensures that we've tested our game against this particular setting and odd behaviour from really large timesteps will be avoided. For example, falling through floors are objects falling through each other when stacked.

#### Variable Timestep

In [Box2D - World](Box2D%20-%20World.md), we either left our code framerate dependent by always stepping our physics world by 1/60th of a second each frame or we passed in deltaTime and had stepped the world at a completely variable time step.

```c++
void Update(float deltaTime)
{
	m_pWorld->Step( 1/60.0f, 8, 3 );
}

void Update(float deltaTime)
{
	m_pWorld->Step( deltaTime, 8, 3 );
}
```

#### Fixed Timestep

What we want to do is only step the world if 1/60th of a second has passed since the last time we stepped the world, and step more than once if needed.

```c++
	float timestep = 1/60.0f;

	m_UnusedTime += deltatime;
	while( m_UnusedTime > 1/60.0f )
	{
		m_pWorld->Step( 1/60.0f, 8, 3 );
		m_UnusedTime -= 1/60.0f;
	}
```

If too little time passed and we don't step the world, we need to clear forces, otherwise forces applied during the next frame will double up on the next step.

```c++
	m_pWorld->ClearForces();
```

#### The Need for Interpolation

This solution has an issue if we're running higher than 60fps.

Our physics simulation will continue to run at 60fps and be stable, but our graphics will run faster.

Our GameObjects are synced to the physics positions each frame, but our physics might not do a step each frame, so our GameObjects might stutter while other non-physics based objects (particles, effects, etc) will be smooth.

To fix this, we'd need to interpolate our objects into place each frame, which would likely mean what we see on screen might be a frame or two behind.
