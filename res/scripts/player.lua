-- MAKE SURE API is registered
-- functions for player class

-- player table
player = {
   sprite = {
      texture_file = "res/images/garg.gif",
      texture_coords = {
	 x = 0, y = 38, w = 32, h = 42
      },
      world_coords = {
	 x = 100, y = 350, w = 32, h = 42
      }
   },   

   --physics  
   speed = 30,
    velx = 0,
    vely = 0,
     

   form = "normal",

   keys = {
      space = false,
      t = false
   }
}

function player.update(dt)

   -- space "released"
   if not kbd.isPressed("space") and player.keys.space then
      player.body:apply_jump(player[player.form].jump)
      player[player.form].onJump()
      player.keys.space = false
   end
   
   -- t "released"
   if not kbd.isPressed("t") and player.keys.t then
      if player.form == "normal" then
	 player.form = "big"
      elseif player.form == "big" then
	 player.form = "normal"
      end
      player[player.form].onTransform()
      player.keys.t = false
   end

   player.velx = 0
   
   if kbd.isPressed("A") then
      player.velx = player.speed * -1.0 * dt
   elseif kbd.isPressed("D") then
      player.velx = player.speed * dt
   end

   player.body:updateInputs(player.velx, player.vely)

   -- save some key "press" to check above for "release"
   for k,v in pairs(player.keys) do
      if kbd.isPressed(k) then
	 player.keys[k] = true
      end
   end
   
end

-- player normal form
player.normal = {
   jump = -20
}

function player.normal.onTransform()
   print("transforming to normal!")
   local newt = gettx("res/images/garg.gif")
   player.mysprite:change_texture(newt)
   player.mysprite:set_texture_and_offset(0, 38, 32, 42)
   fmod.stopEvent("event:/player/transformbig", FMOD_STUDIO_STOP_ALLOWFADEOUT)
end

function player.normal.onJump()
   player.mysprite:set_texture_and_offset(48, 110, 28, 58)
   fmod.playOneShot("event:/player/jump")
end

function player.normal.onLand()
   player.mysprite:set_texture_and_offset(0, 38, 32, 42)
   fmod.playOneShot("event:/player/land")
end

-- player big form
player.big = {
   jump = -14
}

function player.big.onTransform()
   print("transforming to big!")
   local newt = gettx("res/images/big.gif")
   player.mysprite:change_texture(newt)
   player.mysprite:set_texture_and_offset(12, 140, 98, 88)
   fmod.playEvent("event:/player/transformbig")
end

function player.big.onJump()
   player.mysprite:set_texture_and_offset(674, 138, 97, 89)
   fmod.playOneShot("event:/player/jump")
end

function player.big.onLand()
   player.mysprite:set_texture_and_offset(12, 140, 98, 88)
   fmod.playOneShot("event:/player/jump")
end  
