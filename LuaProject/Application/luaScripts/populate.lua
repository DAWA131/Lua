dino_species = "Tyrannosaurus rex"
dino_name = "T-Rex-Kalle"
dino_wings = false

dino_getnoise = function(size)
	local noise = "R"
	for _=1, size do
		noise = noise .. "o"
	end
	noise = noise .. "aar!"
	return noise
end