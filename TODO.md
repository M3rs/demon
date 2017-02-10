# TODO

### Helpful Links
- [Lazy Foo SDL Tutorials](http://lazyfoo.net/tutorials/SDL/index.php)
- [SDL2 API by Category](https://wiki.libsdl.org/APIByCategory)

## Short Term
- Correct player to move as before (probably needs lots of cleanup)
- (in progress) Correct player to transform (swap texture)
- perform draw calls in proper order (right now map is not really ordered)
- Done? Get delta time so movespeed can be in units/sec instead of units/frame

## BUGS
- Transforming into "big" form causes texture to be "off"
  - NB: "Jumping" in big form fixes texture?
- Tranforming from big -> little causes blank texture
  - Jumping fixes this (sort of)

## Collision / Jumping
- re-implement
- Clean up

## Other "game object" / "mobs"
- Publicly accessable: ways to check for collision with another Rect (possibly via sprite)
- unique identifer?

## basic terrain
- different-ish from mob, but not really?

## Animations
- Add basic animation(s)
- Should probably have a texture and a set of IntRects for frames?
 
