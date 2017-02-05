-- MAKE SURE API is registered
-- functions for player class

-- player table
player = {}

-- player normal form
player.normal = {}

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

