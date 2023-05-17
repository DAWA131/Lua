gameMode = 3
currentLevel = "win"
--input spwan pos
force = 10
direction = 0
scene.SetPosition(playerEntity, 350, 280)
scene.RemoveComponent(playerEntity, "jump")

scene.RemoveTile(0, 0)
dofile("luaScripts/maploader.lua")