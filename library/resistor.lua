local r = {
	name = "resistor"
}

function r:gen_geom()
	print("drawing resistor")
end


local c = {
	name = "capacitor"
}

function r:gen_geom()
	print("drawing capacitor");
end


return {r, c}