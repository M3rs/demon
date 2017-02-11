box = {
	sprite = {
		texture_file = "res/images/crate.png",
		texture_coords = {
		x = 0, y = 0, w = 85, h = 86
		},
		world_coords = {
		x = 400, y = 315, w = 85, h = 86
		}
	},
	-- physics
	velx = 0
}

--add function for box eaten
--play a sound, clean up and deregister sprite, etc

function box.update(dt)
-- response to player input?
end