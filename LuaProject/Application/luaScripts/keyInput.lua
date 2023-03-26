--print("Lua: ")
--print(key)
local speed = 1.5

-- Jumping
if key == SPACE then
    scene.SetComponent(playerEntity, "jump", 0)
    force = force + 0.5;
    if force >= 8 then
        force = 8
    end
end

--- Walking
if key == D then
    scene.SetComponent(playerEntity, "rightMove", speed)
end
if key == A then
    scene.SetComponent(playerEntity, "leftMove", speed)
end

---- Released key
if moving == false then
    if key == SPACE then
        scene.SetComponent(playerEntity, "jump", force)
        force = 0
    else
        scene.RemoveComponent(playerEntity, "stop")
    end
end