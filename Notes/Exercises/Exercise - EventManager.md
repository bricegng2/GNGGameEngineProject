
Related:
- [Event Management](../../../PublicNotes/Engine/Event%20Management.md)
- [Function Pointers](../../../PublicNotes/C++%20Details/Function%20Pointers.md)

## Overview

The code is already set up to deal with these event types:
- InputEvent
- CharEvent
- WindowResizeEvent
- RemoveFromGameEvent

Modify it to use an EventManager and all 3 approaches to receiving events as described in [Event Management](../../../PublicNotes/Engine/Event%20Management.md).

## Steps

- Follow the existing event code to see how they're handled
- Create an EventManager class (see [Event Management](../../../PublicNotes/Engine/Event%20Management.md))
	- Follow this class diagram: ![EventSystemClassDiagram](../../../PublicNotes/Images/EventSystemClassDiagram.png)

- Set up the event manager to allow for all 3 methods of sending events simultaneously

#### General Tips

- Be careful with includes, follow these general rules
	- Forward declare if you can. i.e. if you only use a pointer or reference
	- Some things need to be included in headers
		- If you define a new data type with a using statement
		- If you create an instance of the class itself (not a ptr or ref)
		- If you call methods of a class (sometimes needed by templated code)
	- Include headers in your cpp file
		- otherwise you get "can't use incomplete type" errors

#### Method 1

Send all events directly to a virtual Game::OnEvent method.

[#Method1ExtraHelp](#Method1ExtraHelp): See bottom of this document for references if you run into trouble, but please try this out on your own first

#### Method 2

Send events to EventListener subclasses that register themselves for specific event types
- Make the Camera a subclass of EventListener
- Try to handle all event types this way
	- Including changing the Player class to use InputEvents

[#Method2ExtraHelp](#Method2ExtraHelp): See bottom of this document for references if you run into trouble, but please try this out on your own first

#### Method 3

Register functions with the EventManager, so the event manager will directly call methods in your class when event are in the queue.

-  Send events to std::functions that were registered for specific event types
	- Add a new method to the Player class to handle input events
		- Make the Player register this new method with the event manager as a function pointer
		- Modify the player to store a vec2 `m_Controls`, like we've done in the past
		- Handle InputEvents in the new method, setting `m_Controls` as events come in
		- See below for the code for this to save yourself some typing.

#### InputEvent handling code

```c++
// Code to set controls based on events.
if( pEvent->GetType() == fw::InputEvent::GetStaticEventType() )
{
	fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>( pEvent );
	
	if( pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard )
	{
		if( pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed )
		{
			switch( pInputEvent->GetKeyCode() )
			{
			case 'W': case VK_UP:       { m_Controls.y += 1; } break;
			case 'A': case VK_LEFT:     { m_Controls.x += 1; } break;
			case 'S': case VK_DOWN:     { m_Controls.y -= 1; } break;
			case 'D': case VK_RIGHT:    { m_Controls.x -= 1; } break;
			}
		}

		if( pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released )
		{
			switch( pInputEvent->GetKeyCode() )
			{
			case 'W': case VK_UP:       { m_Controls.y -= 1; } break;
			case 'A': case VK_LEFT:     { m_Controls.x -= 1; } break;
			case 'S': case VK_DOWN:     { m_Controls.y += 1; } break;
			case 'D': case VK_RIGHT:    { m_Controls.x += 1; } break;
			}
		}
	}
}
```

## Hic Sunt Dracones

#### Method1ExtraHelp

- Define the EventManager class
	- Put this in your Framework project
	- Add an instance of it to your GameCore
		- This will allow FWCore to access it
	- Pass your GameCore instance (`this`) to the constructor and store it as a member
- Search your code for this exact string: `->OnEvent(`
	- Change all instances of it to call `EventManager->Add()` instead
	- I think there's 4, one for each type of event
- Make sure all 4 event types are allocated on the heap
	- Stack allocated events will go out of scope while the manager is storing their addr

- EventManager::Add will simply push the event into the queue
- EventManager::ProcessEvents will loop through the queue and pass events to GameCore::OnEvent

```c++
	// One way to write EventManager::ProcessEvents
	Event* pEvent = m_Queue.front();
	m_Queue.pop();
	
	m_pGame->OnEvent( pEvent );
	delete pEvent;
```

#### Method2ExtraHelp

- Create a new interface called `EventListener`
	- It just has a single pure virtual method called something other than `OnEvent` to avoid issues with multiple inheritance if we have `Game` inherit from it
- Make any class that you want to receive events directly inherit from `EventListener`
	- This will likely mean multiple-inheritance
	- i.e. `class Game : public GameCore, public EventListener`
- Make that class register for one (or more) specific events
	- `GetEventManager()->RegisterListener( InputEvent::GetStaticEventType(), this );`
- EventManager needs to store a list of Listeners for each event type
	- This can be done fairly well with a map
		- `std::map<EventType, std::vector<EventListener*>> m_Listeners;`
	- Adding `EventListener` objects to the map should be fairly easy
		- Just access the vector and push_back
- In your previously written `EventManager::ProcessEvents` method
	- When pulling Events from the queue, access the correct vector
		- i.e. `std::vector<EventListener*>& list = m_Listeners[pEvent->GetType()]`
	- Then loop through that vector and call the virtual method you created in `EventListener`
