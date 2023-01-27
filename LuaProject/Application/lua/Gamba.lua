function gamble()
	print("Enter name: ")
	local name = io.read()
	print("Enter you luck stat: ")
	luck = io.read("*number")

	local die = math.random(1,6)
	print (die)
	local rez
	if luck > die then
		rez = "won"
	else
		rez = "lost"
	end

	print(name .. ", you " .. rez)
end
