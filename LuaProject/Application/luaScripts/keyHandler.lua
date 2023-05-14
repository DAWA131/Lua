

if gameMode == 1 then
	--Play game
	dofile("luaScripts/keyInput.lua")


end

if gameMode == 2 then
	--Edit game
	dofile("luaScripts/mapEditor.lua")
	
	if key == esc then
		currentLevel = 1
		gameMode = 1

		--input spwan pos
		scene.SetPosition(playerEntity, 250, 580)
		scene.RemoveComponent(playerEntity, "jump")
	end

end