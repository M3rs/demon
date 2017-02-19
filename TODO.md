# TODO

### Helpful Links
- [Lazy Foo SDL Tutorials](http://lazyfoo.net/tutorials/SDL/index.php)
- [SDL2 API by Category](https://wiki.libsdl.org/APIByCategory)

## Short Term
- Store world coords in a Rect struct of our own with float coords
- Move additional physics checks (suspend_x and suspend_y) into lua if they seem useful long-term, so we can have access to change them!
- Player transform polish -- add sounds, change oneshot w/ parameter to starting a mixer snapshot when transformed
- perform draw calls in proper order (right now map is not really ordered)

## BUGS
- TBD (they're there, let's not kid ourselves)

## Collision / Jumping
- Handle landing event

## Other "game object" / "mobs"
- Event to other interested systems when two physicsbodies collide?

## basic terrain
- different-ish from mob, but not really?

## Animations
- Add basic animation(s)
- Should probably have a texture and a set of IntRects for frames?
 
