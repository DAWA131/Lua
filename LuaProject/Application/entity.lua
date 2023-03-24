entity =
{
	name = "David",
	collidable = true,
	position =
	{
		x = 12.34,
		y = 56.78
	}
}

function printEntity(e)
	for k,v in pairs(e) do
		if type(v) == "table" then
			print(k)
			printEntity(v)
		else
			print(k, v)
		end
	end
end