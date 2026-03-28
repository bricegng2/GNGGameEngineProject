
Abstraction Layers, sometimes referred to as Wrappers, are often used in programming to separate higher levels of code from lower level implementation details.

This can be applied to many different components of a game engine

- Graphics
- Physics
- Audio
- Input
- File I/O
- etc

#### Example

As classic example would be rendering engines and this is what the BGFX library is doing.

If we want to make a game engine that supports many different platforms, we need to support many different graphics libraries. For example:
- OpenGL - will run on most devices
- Vulkan - will run on most devices, except OSX and iOS
- DirectX - will run on Windows and Xbox
- Metal - will run on OSX and iOS
- Custom Libaries - notably PlayStation and Switch

If we wanted to support each of these directly, we'd end up with a Mesh class that looks like this:
```c++
Mesh::Draw
{
#if OpenGL
	...
#elif Vulkan
	...
#elif DirectX
	...
#endif
}
```

#### Engine Code

Instead we can write an abstraction layer:

```c++
class OurGraphics
{
	virtual CreateVertexBuffer() = 0;
	virtual CreateIndexBuffer() = 0;
	virtual LoadShader() = 0;
	virtual DrawMesh() = 0;
}
```

Then we can make a version for that interface for each platform we want to support:

```c++
class OurGraphics_OpenGL : public OurGraphics
{
	virtual CreateVertexBuffer() override;
	virtual CreateIndexBuffer() override;
	virtual LoadShader() override;
	virtual DrawMesh() override;
}
```

#### Game Code

Game code will now only use the methods declared in the `OurGraphics` class. They won't know about any of the other versions.

#### Using the Correct Version

The only time you need to be aware of other version is on initialization. There are many options for this, but to limit header includes as much as possible a small helper method with an enum.

For example:
```c++
enum class GraphicsLibraries
{
	OpenGL,
	Vulkan,
	DirectX,
	Metal,
};

OurGraphics* CreateGraphicsLayer(GraphicsLibraries libType)
{
	switch( libType )
	{
	case GraphicsLibraries::OpenGL:
	    return new OurGraphics_OpenGL();
	case GraphicsLibraries::Vulkan:
	    return new OurGraphics_Vulkan();
	case GraphicsLibraries::DirectX:
	    return new OurGraphics_DirectX();
	case GraphicsLibraries::Metal:
	    return new OurGraphics_Metal();
	default:
		assert( false );
	};
}
```

#### Typecasting

To properly abstract the functionality of many different libraries. Game code should never be aware of or be allowed to directly access implementation specific functions. Therefore we shouldn't allow typecasting to these internal types, the only way to discourage this is only let the game code include the wrapper header and not the specific ones.

This is C++, so game code can work around any limitations, but it shouldn't be the default path.
