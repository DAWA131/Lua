
function readLineFromFile(filename, lineNumber)

    -- Open the file in read mode
    local file = io.open(filename, "r")

    if file then
        -- Read the specified line from the file
        local line = file:read("*all"):gsub("\r\n", "\n"):gsub("\r", "\n")
        local lines = {}
        for l in line:gmatch("[^\n]+") do
          table.insert(lines, l)
        end
        
        -- Get the specified line
        local result = lines[lineNumber]
        
        -- Close the file
        file:close()
        
        -- Return the specified line
        return result
    else
        -- If the file can't be opened, return nil
        return nil
    end
end