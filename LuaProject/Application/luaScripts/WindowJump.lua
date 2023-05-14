local width = 48.0

-- Window Collision
if ((playerX + width) > 768) or (playerX < (0 + width)) then
	direction = -direction
	scene.SetComponent(playerEntity, "jump", direction, jumpHeight)
end