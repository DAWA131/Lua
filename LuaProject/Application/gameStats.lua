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

function printStat(stat)
	print(stats[stat])
end

function safeGetStat(stat)
	succeeded, error = pcall(printStat, stat)
	if not succeeded then
		print("Error: " .. error .. "\n")
	end
end