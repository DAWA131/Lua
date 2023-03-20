local transform = {}
local vector = require("vector")
transform.__index = transform

local function new(p, r, s)
	assert(p == nil or vector.isvector(p), "WRONG")
	local t =
		{
			position = p or vector(),
			rotation = r or vector(),
			scale = s or vector()
		}
	return setmetatable(t, transform)
end

local function istransform(t)
	return getmetatable(t) == transform
end

function transform:__newindex(k, v)
	print("No food for you")
end

function transform:__tostring()
	return "Position " .. self.position:__tostring() .. 
	", Rotation " .. self.rotation:__tostring() ..
	", Scale " .. self.scale:__tostring()
end

function transform.__eq(a, b)
	assert(transform.istransform(a) and transform.istransform(b), "NO")
	return a.position==b.position and a.rotation==b.rotation and a.scale==b.scale
end

transform.new = new
transform.istransform = istransform
return setmetatable(transform, {__call = function(_,...) return new(...) end})