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

function r:generate()
	print("generating resistor")
	
	return {
		terminals = {
			a = {pos = {0,  15}, dir = {0,  1}},
			b = {pos = {0, -15}, dir = {0, -1}}
		},
		paths = {
			{"stroke", {-6, -15}, {6, -15}, {6, 15}, {-6, 15}}
		}
	}
end

return {r}