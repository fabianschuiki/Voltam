-- Initialize the signals
local signals
for (i = 0; i < 5; i++)	signals[] = Signal:new("PB"..i)

-- Packages
local p_8P3 = PackageVariant:new("dil8")
local p_8S2 = PackageVariant:new("eiaj8")
local p_S8S1 = PackageVariant:new("soic8")

-- Map the signals.
SignalMapping:new({p_8P3, p_8S2, p_S8S1}, {
	1:	pb5,
	2:	pb3,
	3:	pb4,
	4:	gnd,
	5:	pb0,
	6:	pb1,
	7:	pb2,
	8:	vcc
})
