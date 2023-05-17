local speed = 7.0

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
   force = force + 1.0;
    if force > 15 then
        force = 15
    end
   direction = force
elseif (key1 == SPACE and key2 == A) or (key1 == A and key2 == SPACE) then
    force = force + 1.0;
    if force > 15 then
        force = 15
    end
    direction = -force
end

--- Walking
if key == D and key2 == -1 then
    scene.SetComponent(playerEntity, "move", speed, 0.0, false)
    if scene.HasComponent(playerEntity, "jump") == false and scene.HasComponent(playerEntity, "stop") == false then
        direction = force
    end
end
if key == A and key2 == -1 then
    scene.SetComponent(playerEntity, "move", -speed, 0.0, false)
    if scene.HasComponent(playerEntity, "jump") == false and scene.HasComponent(playerEntity, "stop") == false then
        direction = -force
    end
end

-- Jumping
if key == SPACE then
    scene.SetComponent(playerEntity, "stop")
    force = force + 4.0;
    if force >= 20 then
        force = 20
    end
end

---- Released key
if moving == false then
    if key == SPACE then
        if scene.HasComponent(playerEntity, "jump") == false then
            jumpHeight = force
            force = 10.0
            scene.SetComponent(playerEntity, "jump", direction, jumpHeight)
            scene.RemoveComponent(playerEntity, "stop")
            once = false
        end
    else
        scene.RemoveComponent(playerEntity, "move")
        if scene.HasComponent(playerEntity, "jump") == false then
            direction = 0.0
        end
    end
end