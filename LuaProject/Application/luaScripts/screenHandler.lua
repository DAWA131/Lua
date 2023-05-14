
if (playerY > 850 and gameMode == 1) or (key == 18 and gameMode == 2) then 
	if currentLevel == 2 then
		currentLevel = 1
		scene.RemoveTile(0, 0)

		if gameMode == 1 then
			scene.SetPosition(playerEntity, playerX, 1)
		end

		dofile("luaScripts/maploader.lua")
		print("player above window!")
	end
	if currentLevel == 1 then
		gameMode = 2
	end
end

if (playerY < 0 and gameMode == 1) or (key == 22 and gameMode == 2) then
	if currentLevel == 1 then
		currentLevel = 2
		scene.RemoveTile(0, 0)

		if gameMode == 1 then
			scene.SetPosition(playerEntity, playerX, 849)
		end

		dofile("luaScripts/maploader.lua")
		print("player above window!")
	end
end