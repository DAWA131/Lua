 -- This file will be executed from C , returning this
 -- " behaviour " table to the stack. The C environment
 -- will then populate the table with the following
 -- fields :
 -- self.ID -- the entity ID
 -- self.path -- the path of the this file
 local monster = {}

 monster.lifetime = 3

 -- Guaranteed to be called before OnUpdate from the
 -- C environment.
 -- Can set up more fields in self.
function monster : OnCreate ()
	print ("Monster created!")
end

-- Called once per tick from the C environment.
function monster : OnUpdate ( delta )
	print ("Monster updated!")

	self.lifetime = self.litetime - 1
	if self.litetime <= 0 then
		scene.RemoveEntity(self.ID)
	end
end

return monster