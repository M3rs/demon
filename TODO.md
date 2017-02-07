# TODO

## SDL2
[Download Page][https://www.libsdl.org/download-2.0.php] - will need SDL and SDL_Image libraries. 
- Make SDL, SDL_Image folders in include
- Dump binaries in lib (this might be a good time to organize lib folder, actually, if only to make folders for our different middlewares)


## BUGS
- moving to the left in normal form causes you to FLYYYY off the world

## Collision / Jumping
- Clean up
- Fix height/growth? Is the m_force >= 0 check good enough?

## Other "game object" / "mobs"
- Should have sf::Sprite (to draw and for other stuff)
- Publicly accessable: ways to check for collision with another Rect (possibly via sprite)
- unique identifer?

## basic terrain
- different-ish from mob, but not really?

## Animations
- Add basic animation(s)
- Should probably have a texture and a set of IntRects for frames?

## Organization
- Create `res` folder for resources, with sub folders:
  * `banks` FMOD bank files
  * `images` Any images
  * `scripts` Lua scripts
