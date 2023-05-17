
if (playerY > 850 and gameMode == 1) or (key == 18 and gameMode == 2 and onceMore == true) then 
	onceMore = false
	moving = true
	if currentLevel ~= 1 then
		currentLevel = currentLevel - 1
		scene.RemoveTile(0, 0)

		if gameMode == 1 then
			scene.SetPosition(playerEntity, playerX, 1)
		end

		dofile("luaScripts/maploader.lua")
		return
	end
	if currentLevel == 1 then
		gameMode = 2
		scene.RemoveTile(0, 0)
		dofile("luaScripts/maploader.lua")
	end
end

if (playerY < 40 and gameMode == 1) or (key == 22 and gameMode == 2 and onceMore == true) then
	onceMore = false
	moving = true
	currentLevel = currentLevel + 1
	scene.RemoveTile(0, 0)

	local file = io.open("luaScripts/" .. currentLevel .. ".txt", "r")
	if file then
	-- File exists
	file:close()
	else
	-- File does not exist, create it and fill it with walls
		addEmptyScreen("luaScripts/" .. currentLevel .. ".txt")
	end 

	if gameMode == 1 then
		scene.SetPosition(playerEntity, playerX, 849)
	end

	dofile("luaScripts/maploader.lua")
end


if moving == false and (key == 22 or key == 18)then
	print("key up")
	onceMore = true
end