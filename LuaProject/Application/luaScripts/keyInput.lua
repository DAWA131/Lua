--print("Lua: ")
--print(key)

if key == A then
	print("A")
end
if key == D then
	print("D")
end
if key == SPACE then
	force = force + 2;
	if force >= 50 then force = 50 end
end
if key == nil and force ~= 0 then
	print(force)
	force = 0
end
--some logic for key inputs