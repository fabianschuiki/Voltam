local r = {
	name = "resistor"
}

function r:generate()
	return {
		terminals = {
			a = {pos = {-1.5, 0}, dir = {-1.5, 0}},
			b = {pos = { 1.5, 0}, dir = { 1.5, 0}}
		},
		paths = {
			{	"stroke",
				{-1.5, -0.5},
				{ 1.5, -0.5},
				{ 1.5,  0.5},
				{-1.5,  0.5}
			}
		}
	}
end

return {r}