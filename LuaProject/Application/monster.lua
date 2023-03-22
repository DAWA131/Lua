local monster = {}
monster.lifetime = 3

function monster:OnCreate()
	print("Monster created!")
end

function monster:OnUpdate(delta)
	print("Monster updated!")
	
	self.lifetime = self.lifetime - 1
	if self.lifetime <= 0 then
		scene.RemoveEntity(self.ID)
	end
end

return monster