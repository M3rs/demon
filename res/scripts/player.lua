-- MAKE SURE API is registered
-- functions for player class

-- player table
player = {}

-- player normal form
player.normal = {
   jump = -20
}

function player.normal.onTransform()
   print("transforming to normal!")
   player.change_texture("res/images/garg.gif")
   -- 38, 80
   player.set_texture_and_offset(0, 38, 32, 42)
end

function player.normal.onJump()
   player.set_texture_and_offset(48, 110, 30, 58)
   fmod.playOneShot("event:/player/jump")
end

function player.normal.onLand()
   player.set_texture_and_offset(0, 38, 32, 42)
   --player.set_texture_rect(0, 32, 32, 50)
   fmod.playOneShot("event:/player/land")
end

-- player big form
player.big = {
   jump = -14
}

function player.big.onTransform()
   print("transforming to big!")
   player.change_texture("res/images/big.gif")
   player.set_texture_and_offset(12, 140, 98, 88)
end

function player.big.onJump()
   player.set_texture_and_offset(674, 138, 97, 89)
   fmod.playOneShotWithParameter("event:/player/jump", "transform", 1.0)
end

function player.big.onLand()
   player.set_texture_and_offset(12, 140, 98, 88)
   fmod.playOneShotWithParameter("event:/player/land", "transform", 1.0)
end
