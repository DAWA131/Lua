local mapToLoad = "luaScripts/" .. currentLevel .. ".txt"
local line = readLineFromFile(mapToLoad, 1)
if line == nil then print("ERROR: cant find map file") end
local ofset = 48
local lineNum = 1;

local currentX = 0;
local currentY = 0;
local subStr;

while line ~= nil do
    lineNum = lineNum + 1;
    local line = readLineFromFile(mapToLoad, lineNum)
    if line == nil then
        return
    end
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
                if sub == "a" and gameMode ~= 2 then
                else 
                    local entity = scene.CreateEntity()
                    scene.SetComponent(entity, "drawable", "Overworld/" .. sub .. ".png" , currentX, currentY);
                    if sub ~= "8" then 
                        scene.SetComponent(entity, "collidable", true)
                    end
                    if sub == "8" then
                        scene.SetComponent(entity, "win", true)
                    end
                end
            end
            pos = spacePos + 1
        end
        currentX = currentX + ofset;
    end
    currentX = 0;
    currentY = currentY + ofset;
end