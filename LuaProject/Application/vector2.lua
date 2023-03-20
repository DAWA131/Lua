local vector = {}

function vector.new(x, y, z)
	local t = {
		x = x or 0,
		y = y or 0,
		z = z or 0
		}
	return setmetatable(t, vector)
end

return vector