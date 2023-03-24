local vector = {}

function vector.new(x, y, z)
	local t = {
		x = x or 0,
		y = y or 0,
		z = z or 0
		}
	return setmetatable(t, vector)
end

function vector.isvector(t)
	return getmetatable(t) == vector
end

function vector.__newindex(t, k, v)
	print("Vector - Not possible to assign new fields")
end

function vector.__tostring(t)
	return "(" .. t.x .. ", " .. t.y .. ", " .. t.z .. ")"
end


------------------------------- MATH ---------------------------------

vector.__index = vector
function vector:length()
	return math.sqrt(self.x*self.x + self.y*self.y + self.z*self.z)
end

function vector.__unm(t)
	return vector.new(-t.x, -t.y, -t.z)
end

function vector.__add(a, b)
	assert(vector.isvector(a) and vector.isvector(b), "Vector add expects two vectors")
	return vector.new(a.x+b.x, a.y+b.y, a.z+b.z)
end

function vector.__sub(a, b)
	assert(vector.isvector(a) and vector.isvector(b), "Vector sub expects two vectors")
	return vector.new(a.x-b.x, a.y-b.y, a.z-b.z)
end

function vector.__mul(a, b)
	if type(a) == "number" then
		return vector.new(a*b.x, a*b.y, a*b.z)
	elseif type(b) == "number" then
		return vector.new(a.x*b, a.y*b, a.z*b)
	else
		assert(vector.isvector(a) and vector.isvector(b), "ERROR you shithead")
		return vector.new(a.x*b.x, a.y*b.y, a.z*b.z)
	end
end

function vector.__div(a, b)
	assert(vector.isvector(a) and vector.isvector(b), "ERROR you big shithead")
	if type(b) == "number" then
		return vector.new(a.x/b, a.y/b, a.z/b)
	else
		assert(vector.isvector(b), "ERROR you big shithead")
		return vector.new(a.x/b.x, a.y/b.y, a.z/b.z)
	end
end

function vector.__eq(a, b)
	assert(vector.isvector(a) and vector.isvector(b), "ERROR you big shithead")
	return a.x == b.x, a.y == b.y, a.z == b.z
end

return setmetatable(vector, {__call = function(_,...)
	return vector.new(...)
	end
})