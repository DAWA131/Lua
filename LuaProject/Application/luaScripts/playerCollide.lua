local width = 48.0
local height = 48.0
local pHeight = 50.0

-- Y Collision
-- Jumping up and hitting ceiling
if platformY < playerY then
	jumpHeight = jumpHeight - 2
end

-- Standing on the ground
if platformY + 20 > playerY and (playerX + 30) > platformX and platformY > playerY then
	falling = false
	if once == false then
		once = true
		scene.RemoveComponent(playerEntity, "jump")
		scene.SetComponent(playerEntity, "move", playerX, platformY - (pHeight - 1.0), true)
		if (platformX + 40) > playerX then
			direction = 0.0
		end
	end
end

-- X Collision
-- Right side Collision
if playerX < platformX and (playerX + width) > platformX and playerY > platformY then
	direction = -direction
	scene.SetComponent(playerEntity, "move", platformX - (width + 1), playerY, true)
end

-- Left side Collision
if playerX > platformX and playerX < (platformX + width) and (playerY + height) > (platformY + height) then
	direction = -direction
	scene.SetComponent(playerEntity, "move", platformX + (width + 1), playerY, true)
end