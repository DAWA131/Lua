local vector = {}

function vector.new(x, y, z)
	local t =
	{
		x = x or 0,
		y = y or 0,
		z = z or 0
	}
	return setmetatable(t, vector)
end

function vector.isvector(t)
	if getmetatable(t) == vector then
		print("true")
	else
		print("false")
	end
end

function vector.__newindex(t, k, v)
	print("New field not allowed")
end

function vector.__tostring(t)
	return "(" .. t.x .. ", " .. t.y .. ", " .. t.z ..")"
end

function vector.__unm(t)
	return "(" .. -t.x .. ", " .. -t.y .. ", " .. -t.z ..")"
end

vector.__index = vector

function vector:length()
	return math.sqrt(self.x*self.x + self.y*self.y + self.z*self.z)
end

return setmetatable(vector, {
	__call = function(_,...)
		return vector.new(...)
	end
})