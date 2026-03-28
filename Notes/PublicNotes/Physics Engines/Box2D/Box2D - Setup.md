Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## CMake Setup

The Box2D library comes setup for CMake.

In the root of the Box2D repo (https://github.com/erincatto/box2d) is a cmakelists.txt that will build the library along with some test projects.

We're only interested in the Box2D library itself, that's contained in the **src/CMakeLists.txt** file of their repo.

To include this CMakeLists file in ours, add the following anywhere after the *project* block in our cmake file:
```CMake
include( GNUInstallDirs )
add_subdirectory( Libraries/box2D/src )
```

Finally, add *box2d* to our *target_link_libraries* list of our *Game* project. Our *Game* project is defined in a different CMake file.

It might also be worth setting up the project to compile with C++17, like our other projects:
```CMake
target_compile_features( box2d PRIVATE cxx_std_17 )
```

## Custom Box2D Project Settings

The Box2D library provides a header called `b2_settings.h`.

This file can be used to customize some settings used by the other C++ code in the library.

By default the settings are okay, but we're going to want to customize the `b2BodyUserData` structure a little later. So, we'll want to setup for it.

To do this, we'll copy the entire `#else` block from this file and add it to a new `b2_user_settings.h` file. It has to be in an include path so it can be included with no extra path information.

Now if we set the B2_USER_SETTINGS define in the project settings, the other box2d headers and cpp files will include our `b2_user_settings.h` file in the process, allowing our custom settings to be used.

To do this with CMake first add the define to all projects.
```cmake
add_compile_definitions( B2_USER_SETTINGS )
```

Then give the box2d library a path definition to find the file:
```cmake
target_include_directories( box2d PRIVATE Framework/Source )
```
