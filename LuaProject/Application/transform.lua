local transform = {}
local vector = require("vector")

function transform.new(p, r, s)
	local t =
	{
		position = p or vector.new(),
		rotation = r or vector.new(),
		scale = s or vector.new()
	}
	return t
end

function transform.istransform(t)
	if getmetatable(t) == transform then
		print("true")
	else
		print("false")
	end
end

function transform.__newindex(k, v)
	print("Can not do this")
end

function transform:__tostring(t)
	return "position" .. self.position:__tostring() ..
	", rotation" .. self.rotation:__tostring() ..
	", scale" .. self.scale:__tostring()
end

return transform