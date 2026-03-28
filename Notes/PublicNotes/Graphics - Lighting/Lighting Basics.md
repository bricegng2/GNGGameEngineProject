
### Light Types

- Directional Light
	- Generally to simulate the sun
	- Infinitely far away, so arrives with a fixed direction regardless of where you are
		- assuming you're not simulating the curvature of the earth
- Point Light
	- The most common type of light, since it's fairly easy to calculate
		- Lightbulbs
		- Fireballs
		- anything without a direction
- Spotlight
	- Essentially a point light with a limited cone based on the direction its facing
		- Flashlights
		- Street lights
		- anything with a direction

### Light components

- Ambient
	- General glow on everything in the scene
	- Designed to simulate the many bounces light does around a room
- Diffuse
	- Light that reflects off surfaces in all directions equally
- Specular
	- Light that reflects off surfaces in a specific direction

### Materials

- In the simplest form, material is just a colour, it could come from a texture or from vertex colours interpolated between vertices
- The colour visible on surfaces is a result of which wavelengths of light are absorbed by the surface and which are reflected off of it
- This can be simulated as follows:
```glsl
vec3 materialColour = vec3( 1, 1, 1 );
vec3 lightColour = vec3( 0, 1, 0 );

vec3 litSurfaceColour = materialColour * lightColour;
```
- i.e. If the material is white and the light is green, the surface will be lit green.

### Ambient

- Simply a basic level a light everywhere in the scene
- This is a poor approximation of the light bouncing around the room
	- i.e. A single red light in the scene should give everything a faint red glow
- Simply define a percentage that indicates how much each light will brighten the room

```glsl
float ambientPerc = 0.1;
```

### Diffuse

- The diffuse component of light is the light that reflects in all directions when it hits the surface
- How strong the reflection is is based on the angle the light hits the surface
- This can be approximated by calculating the cosine of the angle between the light and the normal vectors. See [Dot Product](../Math/Dot%20Product.md)
- The dot product can return negative values if the light is behind the surface, so we clamp it to 0 using the max function
- All positions and directions need to be in the same "space", in this case World space works well
	- Light position: will already be defined in your game as a world space position
	- Surface position: will need to come from the vertex shader, ensure it's in world space
	- Normal: will need to come from the vertex shader, ensure it's rotated into world space
- The following code is for a point light
	- For a directional light, the dirToLight would just be a fixed direction
	- For spotlights, we'd do an additional cone check based on the direction the light is facing

```glsl
vec3 dirToLight = normalize( lightPos - surfacePos );

float diffusePerc = max( 0, dot(dirToLight, normal) );
```

### Specular

- The specular component of light is the light that reflects off of the surface in the general direction it was moving
- In this simple form the surface colour (or other surface properties) doesn't affect the reflected colour, so a red light will create a red spot when reflecting off of any surface
- A shininess value will focus the light to reflect in a smaller cone
- Once again, all positions and directions are in world space.

```glsl
vec3 dirToCamera = normalize( cameraPos - surfacePos );
vec3 halfVector = normalize( dirToCamera + dirToLight );

float specularPerc = max( 0, dot(halfVector, v_normal) );
specularPerc = pow( specularPerc, shininess );
```

### Attenuation or Falloff

- For practical reasons, lights should have a range and a curve of falloff over that range
- We'll use the following equation to calculate the falloff
- The falloff exponent will change the curve of the falloff so it's not linear over distance

```glsl
vec3 distanceFromLight = length( lightPos - surfacePos );
float falloff = max( 0, 1 - distanceFromLight/lightRange );
falloff = pow( falloff, falloffExponent );
```

### Mixing it all together

Light is generally additive, if multiple light sources give off light, we can calculate the amount reflected and add that value to other light sources we already calculated.

This also applies to the 3 components of a single light.

```glsl
vec3 ambient = litSurfaceColour * ambientPerc;
vec3 diffuse = litSurfaceColour * diffusePerc;
vec3 specular = lightColour * specularPerc;

vec3 finalColour = ambient + (diffuse + specular) * falloff;
```

All of this is for a single light in a scene. If multiple lights are present, they will each add on to this total, potentially producing color values above 1, which will get clamped by the pipeline code when writing the value into the framebuffer.
