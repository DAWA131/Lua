local width = 48.0
local height = 48.0

-- Y Collision
if platformY < playerY and falling == true then
	
	--scene.SetPosition(playerEntity, playerX, platformY + (height - 1.0))
	--scene.SetComponent(playerEntity, "move", playerX, platformY + (height - 1.0), true)
end

if platformY > playerY and playerX + 40 > platformX then
	falling = false

	--print("PLAYER")
	--print(playerX)
	--print(platformX)

	if once == false then
		scene.RemoveComponent(playerEntity, "stop")
		scene.RemoveComponent(playerEntity, "jump")
		scene.SetComponent(playerEntity, "move", playerX, platformY - (height + 1.0), true)
		direction = 0.0
		print("HEJEKJ")
		once = true
	end
end

-- X Collision
if playerX < platformX and (playerX + width) > platformX and (playerY + height) > (platformY + height) then
	scene.SetComponent(playerEntity, "move", platformX - width, playerY, true)
	--if moving == true then
		
	--else
		--direction = -direction
		--scene.SetComponent(playerEntity, "jump", direction, jumpHeight)
	--end
end

if playerX > platformX and playerX < (platformX + width) and (playerY + height) > (platformY + height) then
	--if moving == true then
		--scene.SetComponent(playerEntity, "move", platformX + width, playerY, true)
	--else
		--direction = -direction
	--end
end