A = 0
D = 3
esc = 36
SPACE = 57
force = 10.0
direction = 0.0
keyDown = -1
key1 = -1
key2 = -1
once = false
onceMore = false
currentLevel = 1
gameMode = 1
jumpHeight = 0.0
fallSpeed = -5.0

--dofile("luaScripts/fileReader.lua")
--dofile("luaScripts/maploader.lua")
dofile("luaScripts/newScreen.lua")
addEmptyScreen("luaScripts/clean2.txt")

playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "player", true);
scene.SetComponent(playerEntity, "collidable", true)
scene.SetComponent(playerEntity, "drawable", "OverWorld/player.png", 250, 600);
print(playerEntity)
