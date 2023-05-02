function replaceChar(file_path, x, y, replacement_char)
    y = y + 1;
    --x = x - 1
    x = x * 2;
    if x % 2 == 0 then x = x + 1 end

    print("replacing on x: " .. x .. " y: " .. y .. " with: " .. replacement_char)

    local file = io.open(file_path, 'r')
    local file_lines = {}
    for line in file:lines() do
        table.insert(file_lines, line)
    end
    file:close()

    -- Calculate the index of the character to be replaced

    local line = file_lines[y]


    local t = string.sub(line, x, x) 
    t = tonumber(t);
    print(t)
    t = t + 1;
    t = t % 10;
    print(t)
    --replacement_char = y;
    --if y ~= 0 then Istile = "a" replacement_char = 0 end
    if string.sub(line, x, x) ~= "0" then Istile = "a" replacement_char = 0 end

    -- Replace the character
    file_lines[y] = string.sub(line, 1, x - 1) .. tostring(t) .. string.sub(line, x + 1)

    local file = io.open(file_path, 'w')
    file:write(table.concat(file_lines, '\n'))
    file:close()
end