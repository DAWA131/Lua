--print("Lua: ")
--print(key)
local speed = 1.5

-- Jumping
if key == SPACE then
    force = force + 2;
    if force >= 8 then
        force = 8
    end
    scene.SetComponent(entity, "jump", 0)
end

--- Moving
if key == D then
    scene.SetComponent(entity, "rightMove", speed)
end
if key == A then
    scene.SetComponent(entity, "leftMove", speed)
end

---- Released key
if moving == false then
    if key == SPACE    then
        scene.SetComponent(entity, "jump", force)
        force = 0
    else
        scene.RemoveComponent(entity, "move")
    end
end