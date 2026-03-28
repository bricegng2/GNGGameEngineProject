
## One time setup

- Download CMake from https://cmake.org
	- You want the "Windows x64 Installer" from the binaries section
	- When installing make sure "Add CMake to the PATH environment variable" is checked
- Check if you have access to my repo: https://github.com/JimmysClass/25W_GG3
	- If not, message me
- Fork the repo
- In your fork:
	- Under Settings -> Collaborators
		- Remove team access

## Cloning your repo

- Use whatever git client you prefer
	- If you use command line
		- add `--recursive` to your clone command
			- `git clone <url> --recursive`
		- if you clone without recursive, run
			- `git submodule update --init`
	- If you use TortoiseGit
		- Check the "recursive" box in the clone window
		- You can also check the "depth" box to reduce the download size
		- If you clone without recursive
			- Find "Git -> Submodule Update" and run that

## Building the game

- Run `GenerateProjectFiles.bat`
- Go into your build folder for the solution file

- If cmake is not part of your default path, add it as the first line in the batch file
	- `set path=%path%;C:\Program Files\CMake\bin`
	- Assuming that's where CMake installed itself

## Create a new mesh

- Add a new mesh to the game that isn't a static list of verts
	- I recommend a circle
	- Watch out for the winding order of the indices
		- Triangles will only appear if the vertices wind around clock-wise

## Useful VS Plugins

- GLSL Language Integration (for VS2022)
	- Not perfect for BGFX shaders, but still worth having
- Open Command Line
	- Allows you to right click a batch file in your solution explorer and execute it
	- Great for GenerateProjectFiles.bat and CompileShaders.bat
- Open File in Solution
	- Allows you to bind a key to quickly open a file based on substring searches
