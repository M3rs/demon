# TODO

### Helpful Links
- [Lazy Foo SDL Tutorials](http://lazyfoo.net/tutorials/SDL/index.php)
- [SDL2 API by Category](https://wiki.libsdl.org/APIByCategory)

## Short Term
- Correct player to move as before (probably needs lots of cleanup)
- Correct player to transform (swap texture)
- Create Renderer method to return the 'sprite' that Player / entity will use; clean up Renderer ref hack in Player
- Create a Renderer registry; perform draw calls in proper order
- Get delta time so movespeed can be in units/sec instead of units/frame


Maybe use something like this:
```cpp
struct RenderInfo {
	SDL_Textue* texture; // SDL_Texture** ?? (no coffee yet, but this hit me as possible)
	SDL_Rect* source;
	SDL_Rect* destination; // position
};
```


## BUGS
- moving to the left in normal form causes you to FLYYYY off the world

## Collision / Jumping
- Clean up
- Fix height/growth? Is the m_force >= 0 check good enough? Handling for "ceiling" collisions?

## Other "game object" / "mobs"
- Should have sf::Sprite (to draw and for other stuff)
- Publicly accessable: ways to check for collision with another Rect (possibly via sprite)
- unique identifer?

## basic terrain
- different-ish from mob, but not really?

## Animations
- Add basic animation(s)
- Should probably have a texture and a set of IntRects for frames?
 
