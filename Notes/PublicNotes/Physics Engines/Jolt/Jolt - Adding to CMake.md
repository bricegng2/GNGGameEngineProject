Tags: #Physics #Jolt [Jolt - !Overview](Jolt%20-%20!Overview.md)

The Jolt library comes setup for CMake

In the Build folder of the Jolt repo (https://github.com/jrouwe/JoltPhysics) are some batch files and a cmakelists.txt that will build the library along with some test projects.

We're only interested in the Jolt library itself, that's contained in: **Build/cmakelists.txt**

To include this cmake file in ours, add the Jolt subdirectory into our main cmake file
```CMake
add_subdirectory( Libraries/JoltPhysics/Build )
```

Finally, add `Jolt` to our `target_link_libraries` list of both the `Framework` and the `GameProject` projects. Our `Framework` doesn't currently have a `target_link_libraries` section, so it will need to be added to the it's `cmakelists.txt` file
```cmake
target_link_libraries( Framework Jolt )
```

Adding Jolt as a target library to our Framework project will add any defines made by the jolt lib to our Framework lib.

Without it, you'll likely end up hitting this assert in `RegisterTypes.h`
```c++
JPH_ASSERT(false, "Version mismatch, make sure you compile the client code with the same Jolt version and compiler definitions!");
```
