
A = 0
D = 3
SPACE = 57
force = 0.0
direction = 0.0
keyDown = -1
key1 = -1
key2 = -1
once = false

local entity = scene.CreateEntity()
--scene.SetComponent(entity, "player", true);
scene.SetComponent(entity, "collidable", true)
scene.SetComponent(entity, "drawable", "OverWorld/border.png");
indicator = entity

--dofile("luaScripts/fileReader.lua")
--dofile("luaScripts/maploader.lua")

playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "player", true);
scene.SetComponent(playerEntity, "collidable", true)
scene.SetComponent(playerEntity, "drawable", "OverWorld/player.png", 500, 700);