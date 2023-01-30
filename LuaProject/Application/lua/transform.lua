local transform = {}

local vector = require("lua/vector")

function transform.new(p, r, s)
	local t = {
		position = p or vector.new(),
		rotation = r or vector.new(),
		scale = s or vector.new()
	}
	return t
end

return transform