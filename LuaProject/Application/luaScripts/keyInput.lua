--print("Lua: ")
--print(key)
local speed = 1.5

--- Walking
if key == D then
    scene.SetComponent(playerEntity, "rightMove", speed, 0.0, false)
end
if key == A then
    scene.SetComponent(playerEntity, "leftMove", speed, 0.0, false)
end

-- Jumping
if key == SPACE then
    scene.SetComponent(playerEntity, "jump", 0.0)
    force = force + 0.5;
    if force >= 8 then
        force = 8
    end
end

---- Released key
if moving == false then
    if key == SPACE then
        scene.SetComponent(playerEntity, "jump", force)
        force = 0
        once = false
    else
        scene.RemoveComponent(playerEntity, "move")
    end
end