
## Current Working Directory

**When an executable is run**, by default it will look for files starting in **it's own folder**.
You can still open files from:
- any relative folder (*"Data/file.txt"*, *"../Data/file.txt"*)
- or absolute folder (*"C:/Data/file.txt"*)

When **launching with the debugger** in Visual Studio, the current working directory defaults to **the project folder**. This can be changed in "Project Settings -> Debugging"

## Code for Reading a File

**fopen approach in C/C++**

```c++
// Headers: <stdio.h>

FILE* pFile = fopen( "myfile.txt", "rb" );
if( pFile )
{
	fseek( pFile, 0, SEEK_END );
	uint32 size = ftell( pFile );
	rewind( pFile );

	char* buffer = new char[size+1];
	fread( buffer, 1, size, pFile );
	fclose( pFile );
	buffer[size] = 0;
}
```

**fstream approach in C++**

```c++
// Headers: <iostream> and <fstream> and <sstream>

ifstream file( "myfile.txt", ios::in|ios::binary );
if( file.is_open() )
{
	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string str = buffer.str();
	file.close();
}
```

## Code for Writing a File

**fopen approach in C/C++**

```c++
// Headers: <stdio.h>

FILE* pFile;
errno_t error = fopen_s( &pFile, "myfile.txt", "wb" );

if( pFile )
{
	fwrite( buffer, strlen(buffer), 1, pFile );
	fclose( pFile );
}
```

**fstream approach in C++**

```c++
// Headers: <iostream> and <fstream>

ofstream file( "myfile.txt", ios::out|ios::binary );
if( file.is_open() )
{
	file.write( str.c_str(), str.size() );
    file.close();
}
```
