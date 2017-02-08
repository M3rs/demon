# TODO

### Helpful Links
- [Lazy Foo SDL Tutorials](http://lazyfoo.net/tutorials/SDL/index.php)
- [SDL2 API by Category](https://wiki.libsdl.org/APIByCategory)

## Short Term
- Correct player to move as before
- Correct player to transform (swap texture)

Maybe use something like this:
```cpp
struct RenderInfo {
	SDL_Textue* texture;
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
 
