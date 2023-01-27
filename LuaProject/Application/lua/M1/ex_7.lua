local stats = 
{
	strength = 4,
	perception = 7,
	endurance = 3,
	charisma = 6,
	intelligence = 9,
	agility = 3,
	luck = 2
}

function printStats()
	for k,v in pairs(stats) do
		io.write(k .. " = " .. v .. "\n")
	end
end

function printStat(a)
	io.write(a .. " = " .. stats[a] .. "\n")
end

function safePrintStat(a)
	if pcall(printStat, a) then

	else
		print("No stat called " .. a)
	end
end
