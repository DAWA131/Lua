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
    local char_index = 1
    local line = file_lines[y]
    local line_length = string.len(line)
    for i = 1, line_length do
        if i > x then
            break
        end
        if string.sub(line, i, i) ~= ' ' then
            char_index = char_index + 1
        end
    end
    char_index = char_index + (y * 2) -- Add 2 characters for each line break

    if string.sub(line, x, x) ~= "0" then Istile = "a" end

    -- Replace the character
    file_lines[y] = string.sub(line, 1, x - 1) .. replacement_char .. string.sub(line, x + 1)

    local file = io.open(file_path, 'w')
    file:write(table.concat(file_lines, '\n'))
    file:close()
end