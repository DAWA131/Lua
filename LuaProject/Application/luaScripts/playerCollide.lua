local width = 48.0
local height = 48.0

-- Y Collision
if platformY > playerY then
	falling = false
	if once == false then
		once = true
		scene.RemoveComponent(playerEntity, "jump")
		scene.SetComponent(playerEntity, "upMove", playerX, platformY - (height - 1.0), true)
	end
end

if platformY < playerY and falling == true then
	scene.SetComponent(playerEntity, "jump", -2.0)
end

-- X Collision
if playerX < platformX and playerX + width > platformX and playerY + height > platformY + height then
	scene.SetComponent(playerEntity, "rightMove", platformX - width, playerY, true)
end

if playerX > platformX and playerX < platformX + width and playerY + height > platformY + height then
	scene.SetComponent(playerEntity, "rightMove", platformX + width, playerY, true)
end