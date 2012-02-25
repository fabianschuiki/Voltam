The following things needs to be done for Voltam.

ToDo
----

- Navigation on the schematic, i.e. zooming and scrolling.
- Adding components to the schematic.
- Choose type of node (two-gate, tri-gate, quad-gate or multi-gate) based on number of terminals that a symbol generates.
- Draw electrical connections (a Node with start and end terminals, and intermediate points).


Classes
-------
Classes that need to be created.

- `Geometry::LuaPath`: Version of `Geometry::Path` exposed to Lua.
- Lua table management class, so things like arguments for symbol rendering can be passed into the symbol scripts.
