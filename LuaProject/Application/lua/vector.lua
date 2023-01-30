local vector = {}

function vector.new(X, Y, Z)
	local t = {
		X = X or 0,
		Y = Y or 0,
		Z = Z or 0
	}
	return t
end


return vector