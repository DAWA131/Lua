local transform = {}

local vector = require("lua/vector")

function transform.new(p, r, s)
	local t = {
		position = p or vector.new(),
		rotation = r or vector.new(),
		scale = s or vector.new()
	}
	return setmetatable(t, transform)
end

function transform.istransform(t)
	return getmetatable(t) == transform
end

function transform.__newindex(t,k,v)
	print("no new fields can be created")
end

function transform.__tostring(t)
	return( "position " .. t.position:__tostring(t.position) .. "\n" .. 
			"rotation ".. t.rotation:__tostring(t.rotation) .. "\n" ..
			"scale    " .. t.scale:__tostring(t.scale))
end

function transform.__eq(a, b)
	assert(transform.istransform(a) and transform.istransform(b), "transform equal - expected args: transform , transform")

	return a.position == b.position and a.rotation == b.rotation and a.scale == b.scale
	
end

return transform