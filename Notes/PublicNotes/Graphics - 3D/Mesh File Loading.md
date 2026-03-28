
## .obj Files

.obj files are an open format used for mesh data

It can generally be imported/exported by all 3d modeling software

The files only store basic geometry data, some programs export more data in a slightly modified format, but that extra data isn’t part of the “standard”, so may not always load correctly in other programs

#### Basic .obj File Format

```
## .obj of a uv-mapped triangle  
v -1 -1 0  
v 1 -1 0  
v 0 1 0  
vt 0 0  
vt 1 0  
vt 0.5 1  
vn 0 0 -1  
f 1/1/1 2/2/1 3/3/1
```

#### Vertex positions

Vertex positions always start with a single ‘v’  
```
v x y z w
```
The ‘w’ is optional and can be ignored for now

example: a sprite at z=0
```
v -1 -1 0  
v 1 -1 0  
v -1 1 0  
v 1 1 0
```

#### UV Coordinates

Texture coordinates start with ‘vt’  
```
vt u v w
```
The ‘w’ is optional and can be ignored for now

example: four texture coordinates for our box
```
vt 0 0  
vt 1 0  
vt 0 1  
vt 1 1
```

#### Vertex Normals

Vertex normals start with ‘vn’  
```
vn x y z
```
example: 2d box with one vertex normal pointing in negative z direction
```
vn 0 0 -1
```

#### Faces

Faces put all of this data together, they start with an ‘f’  
```
f v/vt/vn v/vt/vn v/vt/vn ...
```
The face will have 3 vertices as a minimum, but can have more

example: one quad for our face  
```
f 1/1/1 2/2/1 4/4/1 3/3/1
```

example: two triangles for our face  
```
f 1/1/1 2/2/1 3/3/1  
f 2/2/1 4/4/1 3/3/1
```

Not all .obj files will have uv coordinate and normals

Faces can be in any of the following formats
```
f v v v ...
f v/vt v/vt v/vt ...
f v//vn v//vn v//vn ...
f v/vt/vn v/vt/vn v/vt/vn ...
```

Face attributes will be indexed starting with 1

Faces are stored counter-clockwise

#### Other Details

There are other options that could be used within .obj files
- vertices can be separated into objects and groups
- object lines start with an ‘o’ followed by the name of the object
- group lines start with a ‘g’ followed by the name of the group
- the entire model or a single object/group could have a material file
- material lines start with ‘usemtl’ followed by a filename

All of these can be ignored, but you’ll be left with a single mesh that can only be drawn with a single material

## Parsing the File

Steps to load/parse a basic .obj file
- Load the entire file into a memory buffer
- Parse each line one by one
- For each line:
	- Check what type the line is ‘v’, ‘vt’, ‘vn’ or ‘f’
	- For ‘v’, ‘vt’ and ‘vn’, store the values in a vector for that type
	- For ‘f’ types:
		- Push 3 or more vertices of VertexFormat type into a vector
		- Each VertexFormat will copy values from the other 3 vectors
- Create a new Mesh using the vector of VertexFormat type
- We won't optimize the mesh, so the vertices array will contain a bunch of triangles
	- This makes indices useless, so you can either modify the mesh class to allow for meshes that don't use indices
	- Or, you can simply pass in a list of numbers from 0 -> verts.size(), which is functionally the same, but has some overhead cost that isn't a concern for now

```c++
	long length = 0;
	char* buffer = LoadCompleteFile( objfilename, &length );
	if( buffer == 0 || length == 0 )
	{
		delete[] buffer;
		return;
	}

	// Split the string at line endings
	char* next_token = 0;
	char* line = strtok_s( buffer, "\n", &next_token );

	// Keep looping as long as there are lines:
	while( line )
	{
		// Print out the line to see if it's working.
		OutputMessage( "%s\n", line );

		// TODO: Process the line.

		// Go to the next line
		line = strtok_s( 0, "\n", &next_token );
	}
```

## Breaking down a single line:

#### sscanf / sscanf_s

C++ has a function that can read a formatted string called sscanf
It works with the same string format used for printf
Follow this link for more info: http://www.cplusplus.com/reference/cstdio/sscanf/
Visual studio has marked sscanf as unsafe and provides an alternative sscanf_s
sscanf is considered unsafe because it has no safety mechanism and might write past the end of the buffer provided (aka a Buffer overrun)

#### sscanf example from cplusplus.com (reformatted)

```c++
#include <stdio.h>

void main()
{
    char* sentence = "Rudolph is 12 years old";
    char str[20];
    int i;

    sscanf( sentence, "%s %*s %d", str, &i );
    printf( "%s: %d\n", str, i );
}

Output:
Rudolph: 12
```

#### sscanf_s example from cplusplus.com (reformatted)

```c++
#include <stdio.h>

void main()
{
    char* sentence = "Rudolph is 12 years old";
    char str[20];
    int i;

    sscanf_s( sentence, "%s %*s %d", str, 20, &i );
    printf( "%s -> %d\n", str, i );
}

Output:
Rudolph -> 12
```

#### Simpler working examples (I hope)

```c++
char* sentence = "1"
int value;
sscanf_s( sentence, "%d", &value );
```

```c++
char* sentence = "-1.05"
float value;
sscanf_s( sentence, "%f", &value );
```

```c++
char* sentence = "ready 123"
int value;
sscanf_s( sentence, "ready %d", &value );
sscanf_s( sentence, "%*s %d", &value );
```

```c++
char* sentence = "1/2/3      4/5"
int v[5];
sscanf_s( sentence, "%d/%d/%d %d/%d", &v[0], &v[1], &v[2], &v[3], &v[4] );
```

#### More sscanf_s examples

```c++
    char* sentence = "Rudolph is 12 years old";
    char str[20];
    int i;

    sscanf_s( sentence, "%s %*s %d", str, 20, &i ); // Fills both, returns 2
    sscanf_s( sentence, "%s is %d", str, 20, &i );  // Fills both, returns 2

    sscanf_s( sentence, "%*s %*s %d", &i );         // Fills i, returns 1
    sscanf_s( sentence, "Rudolph is %d", &i );      // Fills i, returns 1

    sscanf_s( sentence, "%s was %d", str, 20, &i ); // Fills str, returns 1
    sscanf_s( sentence, "George is %d", &i );       // returns 0
    sscanf_s( sentence, "George is %d", str );      // mismatch, assert
```

#### Comparing C strings

```c++
	char* line = "test sentence";
	char* line2 = "test sentence";
	
	if( line == line2  ) // Don't match
	
	if( strcmp( line, line2  ) == 0 ) // Match
	
	for( int i=0; i<strlen( line ); i++ ) // Manual string compare
	{
		if( line[i] != line2[i] )
		return false;
		return true;
	}
```

#### Comparing a single character

```c++
	char* line = "v";
	
	if( line == "v" ) // Compare one char* to another
	// This is comparing the addresses to the 2 string
	// Which will not be equal.
	
	if( line[0] == 'v' ) // compare the first character
```

## Next Steps

OBJs are a good first step, but there's very limited data available in these files. We grabbed the core data (positions, uvs and normals), but there's much more you could potentially want in a mesh, like tangents, bitangents, multiple uv channels, animation data, etc.

OBJs support some of that, but not all. GLTF and FBX are likely the most common mesh file formats that supports all the data needed. GLTF is an open format and might have compatibility issues with some tools, while FBX is proprietary and is generally widely supported.

Some libraries that might be worth investigating if you want to go further are:
- AssImp (Asset Importer)
	- https://github.com/assimp/assimp
	- Can load pretty much any file format and present the data to you in it's own internal format, which is simple enough to export as custom binary data that can be loaded quickly into a game engine.
- TinyGLTF
	- https://github.com/syoyo/tinygltf
	- GLTF Format info
		- https://github.com/KhronosGroup/glTF
- OpenFBX
	- https://github.com/nem0/OpenFBX
