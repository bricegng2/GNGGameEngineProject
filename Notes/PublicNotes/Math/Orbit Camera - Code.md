
```c++
vec2 rotationSpeed = vec2( 1.0f, 0.4f );

if( pFramework->IsKeyDown('J') )
	pTransform->m_Rotation.y += 90 * deltaTime * rotationSpeed.x;
if( pFramework->IsKeyDown('L') )
	pTransform->m_Rotation.y -= 90 * deltaTime * rotationSpeed.x;
if( pFramework->IsKeyDown('I') )
	pTransform->m_Rotation.x -= 90 * deltaTime * rotationSpeed.y;
if( pFramework->IsKeyDown('K') )
	pTransform->m_Rotation.x += 90 * deltaTime * rotationSpeed.y;

if( pFramework->IsKeyDown('U') )
	m_Distance -= 10 * deltaTime;
if( pFramework->IsKeyDown('M') )
	m_Distance += 10 * deltaTime;

fw::Clamp( m_Distance, 0.1f, 100.0f );
fw::Clamp( pTransform->m_Rotation.x, -89.9f, 89.9f );

// Calculate eye position.
// Method 1.
float sx = sin( pTransform->m_Rotation.x / 180*PI );
float sy = sin( pTransform->m_Rotation.y / 180*PI );
float cx = cos( pTransform->m_Rotation.x / 180*PI );
float cy = cos( pTransform->m_Rotation.y / 180*PI );
vec3 offset = vec3( cx*sy*m_Distance, -sx*m_Distance, -1*cx*cy*m_Distance );

// Method 2.
mat4 rot;
rot.SetIdentity();
rot.Rotate( pTransform->m_Rotation.x, 1, 0, 0 );
rot.Rotate( pTransform->m_Rotation.y, 0, 1, 0 );
offset = rot * vec3(0,0,-m_Distance);

m_Eye = m_pTarget->m_Position + offset;
m_At = m_pTarget->m_Position;
m_Up = vec3(0,1,0);
```