
## Cross Product

Cross products are useful for a variety of purposes, including:
- Calculating the direction perpendicular to a plane
- Calculating the area of a parallelogram (or a triangle)

![CrossProductParallelogram](../Images/CrossProductParallelogram.png)

### Mechanics

Cross products work in certain dimensions, including 3d.
Mechanically, the cross product operation works like this:

```c++
vec3 result = vec3( 
                    A.y*B.z - A.z*B.y, 
                    A.z*B.x - A.x*B.z,
                    A.x*B.y - A.y*B.x
                  );
```

#### Simplifying for 2D

While the cross product operation isn't defined for 2D, we can look at it as follows:

```c++
float result = A.x*B.y - A.y*B.x;
```

For 2D vectors, we can assume all Z values are 0, this cancels out most of the values resulting in the vector of the form (0,0,z).

Due to this, we can consider a "2D cross product" to return a single float which is the equivalent to the magnitude of the Z value of a 3D cross product.

### Resulting Direction Vector

A cross product of 2 vectors returns a vector parallel to the plane defined by the 2 input vectors

The magnitude of that vector is the area of the parallelogram defined by the 2 input vectors

#### Right hand rule

If you extend your thumb and first 2 fingers of your right hand. Your thumb represents the resulting vector's direction, while your index finger is the left-hand side of cross and your middle finger the right-hand side.

i.e. A x B, should wind counter-clockwise from A to B to produce a vector that extends outward.
Otherwise the result is a vector that points in the opposite direction.

![CrossProductRightHandRule](../Images/CrossProductRightHandRule.png)

Images from Wikipedia
- https://commons.wikimedia.org/wiki/File:Cross_product_parallelogram.svg
- https://commons.wikimedia.org/wiki/File:Right_hand_rule_cross_product.svg
