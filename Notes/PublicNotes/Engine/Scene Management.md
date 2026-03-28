
## Scenes

At the core a Scene is simply a collection of objects. Arguably these objects exist in their own world or in a shared world with other scenes.

All of the higher level managers will only exist in the Game, things like the resource manager, event manager, etc, and are shared between scenes. Again, this is arguable, you might want each scene to handle its own events, other than system event, which would require more than one event manager.

Scenes can be used for maps in a game, minigames, menu pages, or even game modes depending where you put the game logic, for example:
- Main Menu
- Options Menu
- Game
- Pause Menu
- Error Messages
- Notifications
- Confirmation Screens
- etc

## Keeping it Simple

Scene management is all about holding a stack of scenes

Making the structure an actual “std::stack” imposes limits that you may want to avoid, like accessing individual elements of the stack.

A simple array or vector will work nicely

## Scenes in a Stack

Typical progression might look like this for a simple game (skipping steps)

| State 1 | State 2 | State 3 | State 4 |
| ---- | ---- | ---- | ---- |
|  |  |  | Audio Settings |
|  | Game Settings | Audio Settings | Pause Menu |
| Title Screen | Main Menu | Main Menu | Game |

## Pseudo-code of Scene Management Flow

```c++
	pSceneManager->PushScene( “Title Screen” );  
	// Player presses a button  
	pSceneManager->PopAllScenes();  
	pSceneManager->PushScene( “Main Menu” );  
	// Player presses ‘Start Game’  
	pSceneManager->PushScene( “Select Difficulty” );  
	// Game is started  
	pSceneManager->PopAllScenes();  
	pSceneManager->PushScene( “Game” );  
	// Player presses ‘Pause’  
	pSceneManager->PushScene( “Pause Menu” );  
	pSceneManager->Pop(); // Game is resumed, pause menu popped
```

## Some Considerations

If scenes are don't fully cover the scenes below, we must draw the scene under the current one first
If a scene is on top of another, should the scene below receive input
Are all other scenes paused when they’re not on top
- This is especially a concern for network games, we probably don’t want to pause the game if the player pops up a menu

## Drawing Scenes

Since we want some amount of efficiency, the following is a simple way to manage drawing of scenes:
- From the top of the stack, find the first scene that’s opaque    
- Draw that scene and all scenes above it in the stack

If you want more efficiency:
- From the top of the stack, moving downwards, draw all opaque items (Hud elements, menu items, etc)    
- Once you hit an opaque scene, start going up the stack drawing all transparent items

## Handling Input Events

One way to handle input is as follows:
- Pass input events to SceneManager, who will pass them to the top scene
- The event handler function should return a bool indicating if event was used
	- If true: the event shouldn’t go to other objects/scenes    
	- If false: the event should continue to the next object/scene,
		- if no scene used the input event, consider passing it down to the next scene
