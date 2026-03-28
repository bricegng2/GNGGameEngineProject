
## Template Function

Let's start with a simple example: a templated global function

```c++
	template <class TYPE>  
	void Swap(TYPE& v1, TYPE& v2)  
	{  
		TYPE temp = v1;  
		v1 = v2;  
		v2 = temp;  
	}
```

This allows us to call Swap() with any 2 values of the same type  
i.e. int, float, double, char, unsigned char, etc… or even classes/structs

#### Template Function Example Code

Some code that uses the templated function:
```c++
	int int1 = 1;  
	int int2 = 2;  
	float float1 = 3.0f;  
	float float2 = 4.0f;  
	  
	Swap( int1, int2 ); // will swap the values of the 2 ints  
	Swap( float1, float2 ); // will swap the values of the 2 floats
```

Calling Swap with mixed types will cause an compile-time error:
```c++
	int int1 = 1;
	float float1 = 3.0f;
	  
	Swap( int1, float1 ); // error C2782: 'void Swap(TYPE &,TYPE &)' : template parameter 'TYPE' is ambiguous
	  
	// If you want, you can choose a specific global function like this:
	Swap<int>( int1, float1 ); // This should generate a warning
```

When using a templated function, the compiler will generate a function of the type you need when you try to use it

When you call Swap() with 2 ints, internally the compiler will generate:
```c++
    void Swap_int(int& v1, int& v2)
```

When you call it with 2 floats:
```c++
    void Swap_float(float& v1, float& v2)
```

NOTE: names chosen are examples, the compiler will make them more unique

## Templating a Class

The principle works the same way for classes as for functions

```c++
	template <class TYPE>  
	class List  
	{  
	public:  
	    TYPE m_pObjects;  
	  
	    List(unsigned int num)        { m_pObjects = new TYPE[num]; }  
	    ~List()                       { delete[] m_pObjects; }  
	};
```

In order to use a templated class you have to specify the type you want

```c++
    List<int> intList( 100 );

    List<float> floatList( 100 );

    List<GameObject> GameObjectList( 100 );
```

**Note**: Since the compiler is generating the code required at compile time, it needs to know everything about the class being generated.  So, you need to have the entire class definition in a header file.  

## Multiple Types

You can create a template with multiple types:  
```c++
    template <class TYPE1, class TYPE2, class TYPE3>
```

## Class Template Argument Deduction

Template arguments can sometimes be deduced by the compiler.

```c++
// Explicit
std::array<int, 3> data{1,2,3};

// Deduced
std::array data{1,2,3};
```
