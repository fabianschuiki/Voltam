function table.val_to_str ( v )
  if "string" == type( v ) then
    v = string.gsub( v, "\n", "\\n" )
    if string.match( string.gsub(v,"[^'\"]",""), '^"+$' ) then
      return "'" .. v .. "'"
    end
    return '"' .. string.gsub(v,'"', '\\"' ) .. '"'
  else
    return "table" == type( v ) and table.tostring( v ) or
      tostring( v )
  end
end

function table.key_to_str ( k )
  if "string" == type( k ) and string.match( k, "^[_%a][_%a%d]*$" ) then
    return k
  else
    return "[" .. table.val_to_str( k ) .. "]"
  end
end

function table.tostring( tbl )
  local result, done = {}, {}
  for k, v in ipairs( tbl ) do
    table.insert( result, table.val_to_str( v ) )
    done[ k ] = true
  end
  for k, v in pairs( tbl ) do
    if not done[ k ] then
      table.insert( result,
        table.key_to_str( k ) .. "=" .. table.val_to_str( v ) )
    end
  end
  return "{" .. table.concat( result, "," ) .. "}"
end


function main(arguments)
	
	-- Assemble the default arguments.
	args = {
		standard	= "din",
	}
	
	-- Merge the arguments into the defaults.
	for k,v in pairs(arguments) do args[k] = v end
	
	-- Do stuff...
	io.write("Generating resistor «" .. table.tostring(args) .. "»\n")
	s = Symbol()
	
	-- Create the four edge nodes.
	ne = Node()
	ne.x = 1
	ne.y = 0.3
	
	se = Node()
	se.x = 1
	se.y = -0.3
	
	nw = Node()
	nw.x = -1
	nw.y = 0.3
	
	sw = Node()
	sw.x = -1
	sw.y = -0.3
	
	s:addNode("ne", ne)
	s:addNode("se", se)
	s:addNode("nw", nw)
	s:addNode("sw", sw)
	
	-- Create the path whick strokes a line around the for edge nodes.
	path = Path()
	path.closed = true
	path.nodes:push_back("ne")
	path.nodes:push_back("se")
	path.nodes:push_back("sw")
	path.nodes:push_back("nw")
	
	s:addPath("main", path)
	
	-- Add a stroke for the main path.
	stroke = Stroke()
	stroke.path = "main"
	stroke.layer = 1
	
	s.strokes:push_back(stroke)
	
	return s
end

