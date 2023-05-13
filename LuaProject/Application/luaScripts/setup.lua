
A = 0
D = 3
SPACE = 57
force = 0.0
direction = 0.0
keyDown = -1
key1 = -1
key2 = -1
once = false


currentLevel = 1

--dofile("luaScripts/fileReader.lua")
--dofile("luaScripts/maploader.lua")
--dofile("luaScripts/newScreen.lua")
--addEmptyScreen("luaScripts/clean.txt")

playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "player", true);
scene.SetComponent(playerEntity, "collidable", true)
scene.SetComponent(playerEntity, "drawable", "OverWorld/player.png", 250, 600);
print(playerEntity)