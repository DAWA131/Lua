
A = 0
D = 3
SPACE = 57
force = 0;
once = false

--dofile("luaScripts/fileReader.lua")
--dofile("luaScripts/maploader.lua")

local playerEntity = scene.CreateEntity()
scene.SetComponent(playerEntity, "player", true);
scene.SetComponent(entity, "collidable", true)
scene.SetComponent(playerEntity, "drawable", "OverWorld/player.png", 400, 700);