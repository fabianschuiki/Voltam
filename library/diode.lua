local sym = { name = "diode" }
function sym:generate()
	local hw = 10;
	local hh = 10;
	
	return {
		terminals = {
			a = {pos = {-1, 0}, dir = {-1, 0}},
			b = {pos = { 1, 0}, dir = { 1, 0}}
		},
		paths = {
			-- body
			{	"stroke",
				{-1,  1},
				{ 1,  0},
				{-1, -1}
			},
			
			-- bar
			{	"stroke",
				{1,  1},
				{1, -1}
			}
		}
	}
end
return {sym}