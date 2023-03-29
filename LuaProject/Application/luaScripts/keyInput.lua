--local speed = 1.5
local speed = 0.1

-- Checking for two inputs
if moving == true and key1 == -1 then
    key1 = key
elseif moving == true and key1 ~= -1 and key2 == -1 and key1 ~= key then
    key2 = key
elseif moving == false then
    if key1 == key then
        key1 = -1
    elseif key2 == key then
        key2 = -1
    end
end

-- Checking double movement
if (key1 == SPACE and key2 == D) or (key1 == D and key2 == SPACE) then
    direction = 8.0
    force = force + 0.5
    if force >= 8 then
        force = 8
    end
elseif (key1 == SPACE and key2 == A) or (key1 == A and key2 == SPACE) then
    direction = -8.0
    force = force + 0.5;
    if force >= 8 then
        force = 8
    end
end

--- Walking
if key == D and key2 == -1 then
    scene.SetComponent(playerEntity, "rightMove", speed, 0.0, false)
end
if key == A and key2 == -1 then
    scene.SetComponent(playerEntity, "leftMove", speed, 0.0, false)
end

-- Jumping
if key == SPACE then
    scene.SetComponent(playerEntity, "jump", 0.0, 0.0)
    force = force + 0.5;
    if force >= 8 then
        force = 8
    end
end

---- Released key
if moving == false then
    if key == SPACE then
        scene.SetComponent(playerEntity, "jump", direction, force)
        force = 0
        direction = 0.0
        once = false
    else
        scene.RemoveComponent(playerEntity, "move")
    end
end