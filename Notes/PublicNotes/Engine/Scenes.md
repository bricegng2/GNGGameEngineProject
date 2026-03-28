
## Concept

In order to allow our framework to support multiple different scenes and allow the game code to switch between them, we'll need a new `Scene` class.

The `Scene` class will be responsible for managing a set of objects, including:
- Creating objects
- Adding/Removing objects from a list
- Updating objects
- Drawing objects
- Managing the camera
- Checking for collisions
- Other game logic

All the other functionality of the game will stay in the `Game` class. This including loading resource manager, the event manager (although arguably you might want one per scene), uniforms, etc.

## `Scene` base class

- The base `Scene` class doesn't need to do much, it will just be a shim between the `GameObject` and the `Game` classes
	- The `GameObject` class currently knows what game it's currently a part of. This needs to change. GameObjects will now be held by scenes. So every current class that inherits from `GameObject` will now take in a `Scene*` rather than a `GameCore*`

## Game Project `Scene` subclass

- Move all the GameObject creation, update and draw code into this new class
- We'll make one of these for each new scene we want to manage

## `Game` changes

- Add an active scene variable to `Game`, this will need to be updated and drawn each frame

## Optional ideas to take this further

[Scene Management](Scene%20Management.md)
