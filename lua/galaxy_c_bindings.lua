-- Module to define C/Lua bindings used in galaxy.lua

-- Following functions need to be registered in the C source:
-- HOST_randomize_seed_xy (int x, int y)
-- HOST_random_int (int x, int y)
-- HOST_random_double (int x, int y)
-- HOST_draw_char
--

--- 
galaxy = {
	["offset_x"] = 0, 
	["offset_y"] = 0,
	["scroll_left"] = function(time_ms) galaxy["offset_x"] = galaxy["offset_x"] - scroll_speed * time_ms end,
	["scroll_right"] = function(time_ms) galaxy["offset_x"] = galaxy["offset_x"] + scroll_speed * time_ms end,
	["scroll_up"] = function(time_ms) galaxy["offset_y"] = galaxy["offset_y"] - scroll_speed * time_ms end,
	["scroll_down"] = function(time_ms) galaxy["offset_y"] = galaxy["offset_y"] + scroll_speed * time_ms end,
}
rnd = {}

function randomize_seed(x, y)
--	print(string.format("Lua called randomize_seed(%d, %d)", x, y))
	return HOST_randomize_seed_xy(x, y) 
end

function random_int(x, y)
--	print(string.format("Lua called random_int(%d, %d)", x, y))
	return HOST_random_int(x, y)
end

function random_double(x, y)
--	print(string.format("Lua called random_double(%d, %d)", x, y))
	return HOST_random_double(x, y)
end


function galaxy_set_offset(x, y)
	galaxy["offset_x"] = x
	galaxy["offset_y"] = y
end

function draw_string(char, x, y, color)
	HOST_draw_char(char, x, y, color)
end