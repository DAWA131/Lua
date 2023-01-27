local function fizzbuzz(n)

	for i=1, n do
		local line = ""

		if i % 3 == 0 then 
			line = line .. "Fizz"
		end

		if i % 5 == 0 then 
			line = line .. "Buzz"
		end

		if line == "" then 
			line = tostring(i)	
		end

		io.write(line .. "\n")
	end
end

fizzbuzz(15)