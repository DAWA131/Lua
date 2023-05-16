function addEmptyScreen(file_path)
    local x = 16
    local y = 17

    local emptyLine = "";
    for i=1,x do
       if i == 1 then
	    emptyLine = emptyLine .. "5 "
       elseif i == x then
	    emptyLine = emptyLine .. "4 "
       else
	    emptyLine = emptyLine .. "0 "
       end
    end

    local file_lines = {}

    for i=0,y do
	    table.insert(file_lines, emptyLine)
    end

    local file = io.open(file_path, 'w')
    file:write(table.concat(file_lines, '\n'))
    file:close()
end