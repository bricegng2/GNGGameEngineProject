
Barycentric coordinates can measure the property of a vertex at an arbitrary point within a triangle.

It does this using a weighting system based on the areas of the sub-triangle opposite the corner point.

For example the large blue triangle makes up a larger area of the overall triangle, so therefore point 'B' has a bigger influence (more weight) on the final calculation.

![BarycentricCoordinates](../Images/BarycentricCoordinates.png)

#### Area of each Triangle

Each triangle's area can be calculated using a [Cross Product](Cross%20Product.md).

Using very roughly estimated numbers, if we say the areas are as follows:
- overall area of the full triangle is 200
- the red sub-triangle is 40
- the blue sub-triangle is 120
- the green sub-triangle is 40

Then the points have the following weights:
- point A has a height of 40/200 or 0.2
- point B has a weight of 120/200 or 0.6
- point C has a height of 40/200 or 0.2

So, if we're calculating an interpolated colour for point P from 3 corner colours we'd end up with:
20% of colour A + 60% of colour B + 20% of colour C.
