

--replaceChar("luaScripts/test.txt", 17, 17, "Y");

--replaceChar("luaScripts/test.txt", 2, 2, "Y");

--replaceChar("luaScripts/test.txt", 3, 3, "Y");

--addEmptyScreen("luaScripts/test.txt")
if key == 69 then
local tileX = math.floor(mouseX / 48)
local tileY = math.floor(mouseY / 48)

tileY = tileY + 1;

--print("LUA: X: " .. tileX .. " Y: " .. tileY)

Istile = nil
replaceChar("luaScripts/" .. currentLevel .. ".txt", tileX, tileY, "1")
tileY = tileY - 1;

	local currentX = tileX * 48;
	local currentY = tileY * 48;

if Istile == nil then
	local entity = scene.CreateEntity()
	scene.SetComponent(entity, "drawable", "Overworld/" .. 1 .. ".png" , currentX, currentY);

end
if Istile ~= nil then
print("removing a tile")
	scene.RemoveTile(tileX, tileY)
	dofile("luaScripts/maploader.lua")
end

end