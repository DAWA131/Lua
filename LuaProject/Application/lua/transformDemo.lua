local transform = require("lua/transform")

local p = RandomVector(10,20)
local r = RandomVector(30,40)
local s = RandomVector(50,60)

print("pos vector" ,p.X, p.Y, p.Z , "\n")

--t1 = transform.new(p,r,s)
t1 = RandomTransformation(10,100)

print(t1.position.X, t1.position.Y, t1.position.Z)

PrintTransform(t1)