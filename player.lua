-- MAKE SURE API is registered
-- functions for player class

-- player table
player = {}

-- player normal form
player.normal = {}

function player.normal.onTransform()
   print("transforming to normal!")
   player.change_texture("garg.gif")
   player.set_texture_rect(0, 32, 32, 50)
end

function player.normal.onJump()
   player.set_texture_rect(48, 110, 30, 58)
   fmod.playOneShot("event:/player/jump")
end

function player.normal.onLand()
   player.set_texture_rect(0, 32, 32, 50)
   fmod.playOneShot("event:/player/land")
end

-- player big form
player.big = {}

function player.big.onTransform()
   print("transforming to big!")
   player.change_texture("big.gif")
   player.set_texture_rect(12, 140, 98, 88)
end

function player.big.onJump()
   --player.set_texture_rect(48, 110, 30, 58)
   fmod.playOneShot("event:/thor")
end

function player.big.onLand()
   --player.set_texture_rect(0, 32, 32, 50)
   fmod.playOneShot("event:/player/land")
end
