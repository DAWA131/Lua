entity = {
	name = "David",
	collidable = true,
	position = {
		x = 69,
		y = 4.20
	}
}

function printEntity(list, indent)
	indent = indent or ""
	for k,v in pairs(list) do
		if type(v) == "table" then
			io.write(indent .. k .. ":\n")
			printEntity(v, "	")
		else
			io.write(indent .. k .. " = " .. tostring(v) .. "\n")
		end
	end
end
