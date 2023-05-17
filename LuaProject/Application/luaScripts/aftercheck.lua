-- Checking if there is ground under the player
if falling == true then
	if scene.HasComponent(playerEntity, "jump") == false then
		scene.SetComponent(playerEntity, "jump", direction, fallSpeed)
		once = false
		fallSpeed = -5.0
	end
end

-- Making sure the player comes down from a jump
if scene.HasComponent(playerEntity, "jump") == true then
		jumpHeight = jumpHeight - 0.8
		scene.SetComponent(playerEntity, "jump", direction, jumpHeight)
end