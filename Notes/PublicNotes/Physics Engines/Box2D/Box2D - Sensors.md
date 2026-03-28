Tags: #Physics #Box2D [Box2D - !Overview](Box2D%20-%20!Overview.md)

## Sensors

Fixtures can be marked as sensors, which won't react to getting hit.
Any fixture can be set to be a sensor, they can be any shape.
Sensors will still give you a BeginContact callback, so you can tell if something collided with them.

#### Sensors as Event Triggers

Sensors can be used for many things, including static/dynamic event triggers in your game.
Since you can add multiple fixtures to an object, you can have solid objects with sensor shapes attached.