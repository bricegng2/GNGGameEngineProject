
## Optimize the Sprite mesh

The sprite mesh is currently set to use 6 vertices. This can be reduced to the 4 unique vertices, and the indices list can be adjusted to reuse some of the vertices.

## Create a new mesh

- Add a new "procedural" circle mesh to the game
	- Unlike the other meshes, this can't simply be a static list of verts
		- Write a function that will generate a list of vertices and indices
		- You can cut and paste old code from last semester, but since we didn't use indices, you'll have to adapt it
		- This new codebase is limited to rendering with Triangles
			- i.e. We don't have triangle strips or fans
	- Watch out for the winding order of the indices
		- Triangles will only appear if the vertices wind around clock-wise
