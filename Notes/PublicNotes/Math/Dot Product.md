
## Dot Product

a.k.a. Inner Product, Scalar Product

Calculating a dot product is so simple that it has become a popular choice for many game calculations.

Mechanically, the operation is as follows:
```
	A · B = A.x*B.x + A.y*B.y + A.z*B.z;
```
This would continue for more dimensions if needed

While easy to calculate the dot product has some interesting properties, including this one:
```
	A · B = |A||B|cos(θ)
```

If you want a full explanation of why this is true, you can read more here:
http://www.mit.edu/~hlb/StantonGrant/18.02/details/tex/lec1snip2-dotprod.pdf

## Relationship between Vectors

To simplify `A · B = |A||B|cos(θ)`, we can assume the 2 vectors are normalized. This would replace the 2 lengths with the number 1 and reduce the equation to:
```
	A · B = cos(θ)
```

i.e. the dot product of 2 unit vectors is the cosine of the angle between those 2 vectors.

Examples:
![VectorRelationships](../Images/VectorRelationships.png)

If 2 vectors are pointing in the same direction we get a value of 1
Opposing vectors will give -1
Perpendicular vectors will give 0
Everything in between will give values along the arc of a circle

![CosArc](../Images/CosArc.png)

This can be converted into a angle with an inverse cosine if needed:

```
	angle in radians = acos( dot product result )
```
