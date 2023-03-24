function gamble()
	print("Enter name: ")
	local name = io.read()
	print("Enter your luck stat: ")
	luck = io.read("*number", "*1")

	local die = math.random(1, 6)
	print(die)
	local result

	if luck > die then
		result = "won"
	else
		result = "lost"
	end

	print(name .. ", you " .. result)
end