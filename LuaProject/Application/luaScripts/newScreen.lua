function addEmptyScreen(file_path)
    local x = 16
    local y = 17

    local emptyLine = "";
    for i=0,x do
	   emptyLine = emptyLine .. "0 "
    end

    local file_lines = {}

    for i=0,y do
	    table.insert(file_lines, emptyLine)
    end


    
    local file = io.open(file_path, 'r')
    for line in file:lines() do
        table.insert(file_lines, line)
    end
    file:close()

    local file = io.open(file_path, 'w')
    file:write(table.concat(file_lines, '\n'))
    file:close()
end