
## Const Variables

Const types can't be changed once set

```c++
const int constValue = 5;

// error C3892: 'constValue': you cannot assign to a variable that is const
constValue = 9; // Not allowed.
```

This also means you can only make const references to const values

```c++
// error C2440: 'initializing': cannot convert from 'const int' to 'int &', Conversion loses qualifiers
int& nonConstValueRef = constValue; // Not allowed

const int& constValueRef = constValue;
```

And you can't pass them into methods that only access const reference arguments

```c++
void AddTo(int& total, int valueToAdd);

// error C2664: 'void AddTo(int &,int)': cannot convert argument 1 from 'const int' to 'int &', Conversion loses qualifiers, see declaration of 'AddTo', while trying to match the argument list '(const int, int)'
AddTo( constValue, 5 ); // Not allowed.
```

This, of course, applies to both built-in types as well as custom classes and structs

```c++
const vec2 constPosition( 50, 75 );

void Mesh::Draw(vec2& pos);

mesh.Draw( constPosition ); // Not allowed.
```

## Const Methods

When defining a class, we can declare whether or not methods are const. A const method would be something that doesn't change the class in any way.

```c++
void vec2::Length() const
{
	return sqrt(x*x + y*y);
}
```

Modifying members while in a const method isn't allowed. A const method essentially treats the object its inside as const, even if it wasn't const in the context where it was called.

```c++
void vec2::Normalize() const
{
	float length = Length();
	
	//error C3490: 'x' cannot be modified because it is being accessed through a const object
	x /= length; // Not allowed.
	y /= length; // Also not allowed.
}
```
