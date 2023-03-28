-- Y Collision
if platformY > playerY then
	collide = true
	if once == false then
		once = true
		scene.RemoveComponent(playerEntity, "jump")
	end
end

--if platformY < playerY then
	--scene.SetComponent(playerEntity, "jump", -3.0)
--end

-- X Collision
--elseif platformX > playerX then
	--scene.SetComponent(playerEntity, "rightMove", platformX - 48.0, true)
--elseif platformX < playerX then
	--scene.SetComponent(playerEntity, "rightMove", platformX + 48.0, true)
--end