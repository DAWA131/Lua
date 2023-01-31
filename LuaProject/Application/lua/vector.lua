local vector = {}

function vector.new(X, Y, Z)
	local t = {
		X = X or 0,
		Y = Y or 0,
		Z = Z or 0
	}
	return setmetatable(t, vector)
end

function vector.isvector(t)
	--return getmetatable(t) == vector
	return getmetatable(t) == vector
end

function vector.__newindex(t, k, v)
	print("vector - not possible to assign new fields")
end

function vector.__tostring(t)
	return("(" .. t.X .. ", " .. t.Y .. ", " .. t.Z .. ")")
end

function vector.__unm(t)
	return vector.new(-t.X, -t,Y, -t.Z)
end

function vector.__add(a, b)
	assert(vector.isvector(a) and vector.isvector(b), "vector add - expected args: vector , vector")
	return vector.new(a.X + b.X, a.Y + b.Y, a.Z + b.Z)
end

function vector.__sub(a, b)
	assert(not isvector(a) or not isvector(b), "vector add - expected args: vector , vector")
	return vector.new(a.X - b.X, a.Y - b.Y, a.Z - b.Z)
end

function vector.__mul(a, b)
	if type(a) == "number" then 
		return vector.new(b.X * a, b.Y * a, b.Z *a)
	end
	if type(b) == "number" then
		return vector.new(a.X * b, a.Y * b, a.Z *b)
	end
	if vector.isvector(a) and vector.isvector(b) then
		return vector.new(a.X * b.X, a.Y * b.Y, a.Z * b.Z)
	end
	assert(false, "vector mul - expected args: vector or number")
end

function vector.__div(a, b)
	if type(a) == "number" then 
		return vector.new(b.X / a, b.Y / a, b.Z / a)
	end
	if type(b) == "number" then
		return vector.new(a.X / b, a.Y / b, a.Z / b)
	end
	if vector.isvector(a) and vector.isvector(b) then
		return vector.new(a.X / b.X, a.Y / b.Y, a.Z / b.Z)
	end
	assert(false, "vector div - expected args: vector or number")
end

function vector.__eq(a, b)
	assert(vector.isvector(a) and vector.isvector(b), "vector add - expected args: vector , vector")
	return a.X == b.X and a.Y == b.Y and a.Z == b.Z
end

vector.__index = vector
function vector:length ()
	return math.sqrt(self.X*self.X + self.Y*self.Y + self.Z*self.Z)
end

return vector