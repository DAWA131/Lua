


if playerY > 850 then 
	if currentLevel == 2 then
		currentLevel = 1
		scene.RemoveTile(0, 0)
		scene.SetPosition(playerEntity, playerX, 1)

		dofile("luaScripts/maploader.lua")
		print("player above window!")
	end
end

if playerY < 0 then
	if currentLevel == 1 then
		currentLevel = 2
		scene.RemoveTile(0, 0)
		scene.SetPosition(playerEntity, playerX, 849)

		dofile("luaScripts/maploader.lua")
		print("player above window!")
	end
end