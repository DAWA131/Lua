
A = 0
D = 3
SPACE = 57
force = 0;

--dofile("luaScripts/fileReader.lua")

--dofile("luaScripts/maploader.lua")

local entity = scene.CreateEntity()
scene.SetComponent(entity, "player", true);
scene.SetComponent(entity, "drawable", "OverWorld/1.png");

entity = scene.CreateEntity()
scene.SetComponent(entity, "player", true);
scene.SetComponent(entity, "drawable", "OverWorld/7.png", 400, 750);