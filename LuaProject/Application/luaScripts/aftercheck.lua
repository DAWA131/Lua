if falling == true then
	if scene.HasComponent(playerEntity, "jump") == false then
		scene.SetComponent(playerEntity, "jump", direction, -force)
		once = false
	end
end

if scene.HasComponent(playerEntity, "jump") == true then
	jumpHeight = jumpHeight - 0.03
	scene.SetComponent(playerEntity, "jump", direction, jumpHeight)
end