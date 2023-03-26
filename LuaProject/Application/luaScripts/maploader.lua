--local fileReader = require("readLineFromFile")

print("start")
local line = readLineFromFile("luaScripts/map.txt", 1)
if line == nil then print("ERROR: cant find file") end
local ofset = line
local lineNum = 1;

local currentX = 0;
local currentY = 0;
local subStr;

while line ~= nil do
    lineNum = lineNum + 1;
    local line = readLineFromFile("luaScripts/map.txt", lineNum)

    local pos = 1
    while true do
        local spacePos, tabPos = string.find(line, "[%s\t]", pos)
        if not spacePos and not tabPos then
            break
        end
        if spacePos then
            subStr = string.sub(line, pos, spacePos) 
            sub = string.match(subStr, "%S+")
            if sub ~= "0" then
                print("elemnt found name: " .. sub .. "with pos Y: " .. currentX .. "and Y: " .. currentY)
                entity = scene.CreateEntity()
               -- scene.SetComponent(entity, "player", true);
               scene.SetComponent(entity, "collidable", true)
               scene.SetComponent(entity, "drawable", "Overworld/" .. sub .. ".png" , currentX, currentY);
            end
            pos = spacePos + 1
        end
        if tabPos and tabPos ~= spacePos then
            print("Tab position:", tabPos)
            pos = tabPos + 1
        end
        currentX = currentX + ofset;
    end
    currentX = 0;
    currentY = currentY + ofset;
end

print(string.sub(line, pos))

print("-----------");


print(line);