if falling == true then
	if scene.HasComponent(playerEntity, "jump") == false then	
		scene.SetComponent(playerEntity, "jump", 0.0, -2.0)
		once = false
	end
end