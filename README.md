Voltam
======
Voltam is a Printed Circuit Board CAD tool.

The *schematic* editor allows you to draw an electronic circuit schematically by
placing and interconnecting varioud components.

The *board* editor allows you to use a previously drawn schematic as a reference
by which you place the components' physical packages on a PCB and route the
electrical connections between them.


Philosophy
==========
Most tools for designing PCBs are either expensive or very cumbersome to use.
If you are working on a more or less sophisticated design you usually end up
spending more time drawing schematic symbols and package outlines for the
components you want to use than actually placing and connecting them. This is
because most of these tools use a rather static approach when it comes to
component libraries. Usually there's one device that consists of a symbol and
multiple packages. Everytime you want a new device, you draw a new symbol and
copy some package drawings that are hopefully already around.

Voltam takes a __very different__ approach on libraries and component use by
introducing elements of *object-oriented programming* to the PCB world.


Dynamic Symbol/Package/Device Generation
----------------------------------------
Using Lua scripting you don't create symbols, packages or devices directly but
rather write a generator script that creates them on the fly based on your
requirements.

Take diodes for an example: Instead of creating the symbols `diode.sym`,
`schottky.sym` and `zener.sym` you would write a generator script called
`diode.lua` that takes an argument `type=(normal|schottky|diode)`. Now whenever
you need a schottky diode symbol somewhere, you just say something like `diode
type=schottky`. The generator will create the appropriate symbol for you.


Device Inheritance
------------------
To allow for rapid growth of the component library, keeping information reuse to
a minimum is paramount. This is where inheritance comes into play which allows
you to generalize certain device attributes and qualities in device superclasses
which devices may inherit from.

Take the diodes again for an exmaple: Schottky and zener diodes are actually
diodes that have some special attributes. It makes sense that a zener diode
doesn't have to define itself as a diode again but reuse the information
attributed to diodes in general.

So you would create a device `diode.dev` that specifies the `diode.sym` as
its schematic symbol and adds `Vdrop` as an essential attribute of the part.
This is a diode in most general terms: It has a dropout voltage and can either
be a normal, schottky or zener diode.

Now you would create a device `zener.dev` that *inherits* from `diode.dev`. At
this point, the new device is just a copy of the original diode. Now you add
`type=zener` to the symbol arguments and add `Vz` as an essential attribute.

Usually devices that have a characteristic attribute like the zener voltage `Vz`
come in series where a manufacturer creates a bunch of similar devices that only
vary in that certain attribute. Take the `BZX 384` zener diode series from NXP
as an example: You would create a device generator script `bzx384.lua` that
reads a list of zener voltages and create a new device inheriting from
`zener.dev` for each row in the list.

Device inheritance allows you to create a billion devices from little
information. You say "zener diode" with voltages `2.7, 3.3, 4.3, 4.7, ...` and
part name `BZX 384-C${Vz}` and end up being able to search for and add the
device `BZX 384-C4V3` to your schematic diagram.

