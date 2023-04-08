

--replaceChar("luaScripts/test.txt", 17, 17, "Y");

--replaceChar("luaScripts/test.txt", 2, 2, "Y");

--replaceChar("luaScripts/test.txt", 3, 3, "Y");

--addEmptyScreen("luaScripts/test.txt")

local tileX = math.floor(mouseX / 48)
local tileY = math.floor(mouseY / 48)

tileY = tileY + 1;

--print("LUA: X: " .. tileX .. " Y: " .. tileY)

Istile = nil
replaceChar("luaScripts/map.txt", tileX, tileY, "2")
tileY = tileY - 1;


if Istile == nil then
	local currentX = tileX * 48;
	local currentY = tileY * 48;
	entity = scene.CreateEntity()
	scene.SetComponent(entity, "player", true);
	scene.SetComponent(entity, "drawable", "Overworld/" .. 2 .. ".png" , currentX, currentY);
end

--print("done")