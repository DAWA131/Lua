if collide == false then
	if scene.HasComponent(playerEntity, "jump") == false then	
		scene.SetComponent(playerEntity, "jump", -3.0)
		once = false
	end
end