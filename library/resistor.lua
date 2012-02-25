local r = {
	name = "resistor"
}

function r:gen_geom()
	print("drawing resistor")
	
	local p = Path:new()
	p:moveTo(-6, -15)
	p:lineTo( 6, -15)
	p:lineTo( 6,  15)
	p:lineTo(-6,  15)
	
	return p
end


local c = {
	name = "capacitor"
}

function c:gen_geom()
	print("drawing capacitor")
end

return {r, c}