if (playerX + 48) >= 768 then
	scene.SetPosition(playerEntity, playerX - 50, playerY, true)
end

if playerX < 0 then
	scene.SetPosition(playerEntity, playerX + 50, playerY, true)
end