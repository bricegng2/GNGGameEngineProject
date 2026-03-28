Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

#### Contact between fixtures

In Box2D, contacts aren’t necessarily collisions. If the AABB of two fixtures overlap, a contact object will be created.

The following 2 shapes are considered as being in contact. The contact object will exist, but calling it’s IsTouching() method will return false.

![Box2D Overlap](../../Images/Box2D%20Overlap.png)

#### Contact List

Box2D has a list of all current contacts, which you can access as follows:
```c++
m_pWorld->GetContactList()
```

The contact list will contain all contacts, including those where no collision/overlap exists.

To be informed of contacts that involve a collision, we will use a contact listener.

#### Contact Listener

b2ContactListener is an interface class that provides contact information whenever 2 fixtures collide.

Similar to the way b2Draw works for drawing debug info, the b2ContactListener class has 4 virtual functions that you can override:

- BeginContact()    
- EndContact()    
- PreSolve()    
- PostSolve()    

These functions are not pure virtual, so an override doesn’t need to be provided.

#### Setting up the Contact Listener

A b2ContactListener derived class must be associated with the world. So, we need to create a subclass of b2ContactListener and then in PhysicsWorld2D, create an instance of it and associate it with the b2World.

```c++
m_pContactListener = new CustomContactListener();  
m_pWorld->SetContactListener( m_pContactListener );
```

#### Contacts

All 4 of the contact listener callback functions will pass in a b2Contact class.

The b2Contact class holds the following, among other things:
- flag for various things including “is touching”    
- pointers to the 2 fixtures involved in the contact    
- contact normal    
- contact manifold - contains local space contact information for both fixtures

#### User Data

When we create a body, we can set any pointer as user data for that body. When a contact is made, we can retrieve the user data.

Without customizing the userdata structure in b2_settings.h, we can set user data with a typecast:
```c++
// Set user data:
// when creating a body, give it a pointer to the gameobject  
bodydef.userData.pointer = (uintptr_t)this;

// Get user data:
GameObject* pGO = static_cast<GameObject*>(
    contact->GetFixtureA()->GetBody()->GetUserData().pointer );
```

if you did customize the user data (see [Box2D - Setup](Box2D%20-%20Setup.md)), you can skip the typecasts:
```c++
// Set user data:
// when creating a body, give it a pointer to the gameobject  
bodydef.userData.pGameObject = this;

// Get user data:
GameObject* pGO = contact->GetFixtureA()->GetBody()->GetUserData().pGameObject;
```

#### BeginContact()

When two fixtures touch, you will receive a call to BeginContact().

In order to keep our ContactListener class as game agnostic as possible, we'll pass that contact info to the Game through an event. The Game can then decide what to do with it.

You'll probably want to send various pieces of data, such as GameObjects, collision normals and more, but we don't want that info to be Box2D specific, so avoid sending anything like b2Fixture or b2Body.

#### GameObject pointer from UserData

When initially creating the physics body, we set the "user data" to be a pointer to the GameObject that represents the physics body, to get it back from the collision contact info, we can do the following:

```c++
// Assumes userdata was customized in b2_user_settings.h
pObjA = contact->GetFixtureA()->GetBody()->GetUserData().pGameObject;
pObjB = contact->GetFixtureB()->GetBody()->GetUserData().pGameObject;
```

#### EndContact()

When the two fixtures separate, you will receive a call to EndContact(). Again, you can pass this along to your GameObject class if needed

#### Using Begin/End to Enable Jumping

In a pretty rudimentary way, you could easily use these 2 callbacks to decide if your player can jump

```c++
    void GameObject::BeginContact(...)  
    {  
        m_JumpAllowed = true;  
    }  
  
    void GameObject::EndContact(...)  
    {  
        m_JumpAllowed = false;  
    }
```

but this isn't a great approach, since if your player is walking on the ground and reaches a hill

![Box2D BeginEndContact](../../Images/Box2D%20BeginEndContact.png)

As you saw, just setting a flag for AllowJumping isn't going to be enough.

You can solve this by storing a count of how many fixtures your player is currently colliding with.

This will solve this particular issue, but consider the following:
- You don't want to be able to jump if the player is colliding with things other than the ground
- You might want to allow the player a bit of leeway, so he can still jump even if he stepped off the ground recently.  This is also applicable for slightly uneven ground.

#### PreSolve/PostSolve

The PreSolve and PostSolve functions, as described in the comments in the b2ContactListener code can be used to inspect the state of the contact before and after the internal contact "solver" figures out how to separate the fixtures

The most common use of these overrides is to ignore specific collisions by calling the following
```c++
contact->setEnabled( false );
```
