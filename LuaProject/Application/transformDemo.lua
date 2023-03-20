local transform = require("transform")

local p = RandomTransform(10, 20)
local r = RandomTransform(40, 70)
local s = RandomTransform(20, 80)

print("P2: ")
print(p.x)

local t1 = transform.new(p, r, s)
PrintTransform(t1)