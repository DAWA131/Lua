local health = 100
print("HRJRJ")

for _=1,100 do
	local entity = scene.CreateEntity()
	local tickDamage = math.random(1,10)
	scene.SetComponent(entity, "health", health)
	scene.SetComponent(entity, "poison", tickDamage)
end