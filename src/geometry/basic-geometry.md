<!--?title Basic point handling -->

# Basic point handling

In this article we will consider basic operations on points in euclidean space which maintain the foundation of whole analytical geometry.
## Linear operations
Both 2D and 3D points maintain linear space, which means that for them sum of points and multiplication of point by some number are defined. Here are those basic implementations for 2D:

```cpp
struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}
    point2d operator += (const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d operator -= (const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d operator *= (ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d operator + (const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator - (const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator * (ftype t) const {
        return point2d(*this) *= t;
    }
};
point2d operator * (ftype a, point2d b) {
    return b * a;
}
```
And 3D points:
```cpp
struct point3d {
    ftype x, y, z;
    point3d() {}
    point3d(ftype x, ftype y, ftype z): x(x), y(y), z(z) {}
    point3d operator += (const point3d &t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d operator -= (const point3d &t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d operator *= (ftype t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d operator + (const point3d &t) const {
        return point3d(*this) += t;
    }
    point3d operator - (const point3d &t) const {
        return point3d(*this) -= t;
    }
    point3d operator * (ftype t) const {
        return point3d(*this) *= t;
    }
};
point3d operator * (ftype a, point3d b) {
    return b * a;
}
```

Here `ftype` is some class you use for coordinates, usually `int`, `double` or `int64_t`.

## Dot product

### Definition
Dot (or scalar) product $\mathbf a \cdot \mathbf b = (\mathbf a,\mathbf b)$ for vectors $\mathbf a$ and $\mathbf b$ can be defined in two identical ways. Geometrically it is product of length of first vector by length of projection of second vector onto first one. As you may see from image below this projection is nothing but $|\mathbf b| \cos \theta$ where $\theta$ is the angle between $\mathbf a$ and $\mathbf b$. Thus $(\mathbf a, \mathbf b) = |\mathbf a| \cdot |\mathbf b| \cos \theta$.

<center>![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3e/Dot_Product.svg/300px-Dot_Product.svg.png)</center>

Dot product holds some notable properties:

1. $(\mathbf a, \mathbf b) = (\mathbf b, \mathbf a)$
2. $(\alpha \cdot \mathbf a, \mathbf b) = \alpha (\mathbf a, \mathbf b)$
3. $(\mathbf a + \mathbf b, \mathbf c) = (\mathbf a, \mathbf c) + (\mathbf b, \mathbf c)$

I.e. it's commutative function which is linear with respect to both arguments. Let's denote unit vectors as

$$\mathbf e_x = \begin{pmatrix} 1 \\\ 0 \\\ 0 \end{pmatrix}, \mathbf e_y = \begin{pmatrix} 0 \\\ 1 \\\ 0 \end{pmatrix}, \mathbf e_z = \begin{pmatrix} 0 \\\ 0 \\\ 1 \end{pmatrix}$$

With this notation we can write vector $\mathbf r = (x;y;z)$ as $r = x \cdot \mathbf e_x + y \cdot \mathbf e_y + z \cdot \mathbf e_z$. And since for unit vectors 

$$(\mathbf e_x, \mathbf e_x) = (\mathbf e_y, \mathbf e_y) = (\mathbf e_z, \mathbf e_z) = 1,\\\
(\mathbf e_x, \mathbf e_y) = (\mathbf e_y, \mathbf e_z) = (\mathbf e_z, \mathbf e_x) = 0$$

We can see that in terms of coordinates for $\mathbf a = (x_1;y_1;z_1)$ and $\mathbf b = (x_2;y_2;z_2)$ holds

$$(\mathbf a, \mathbf b) = (x_1 \cdot e_x + y_1 \cdot e_y + z_1 \cdot e_z, x_2 \cdot e_x + y_2 \cdot e_y + z_2 \cdot e_z) = x_1 x_2 + y_1 y_2 + z_1 z_2$$

That is also algebraic definition of dot product. From this we can write functions which calculate it.

```cpp
ftype dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}
ftype dot(point3d a, point3d b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
```

When solving problems one should use algebraic definition to calculate dot products, but keep in mind geometric definition and properties to use it.
### Properties
We can define many geometrical properties via dot product. For example 

1. Length and norm (squared length): $|\mathbf a|^2=(\mathbf a, \mathbf a)$
2. Projection of $\mathbf a$ onto $\mathbf b$: $\dfrac{(\mathbf a, \mathbf b)}{|\mathbf b|}$.
3. Angle between vectors: $\arccos \dfrac{(\mathbf a, \mathbf b)}{|\mathbf a| \cdot |\mathbf b|}$.
4. From the previous point we may see that dot product is positive if angle between them is acute, negative if it's obtuse and equals zero if they're orthogonal, i.e. they form right angle.

Note that all these functions do not depend on number of dimensions hence they will be same for 2D and 3D case:

```cpp
ftype norm(point2d a) {
    return dot(a, a);
}
double abs(point2d a) {
    return sqrt(norm(a));
}
double proj(point2d a, point2d b) {
    return dot(a, b) / abs(b);
}
double angle(point2d a, point2d b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
```

To see the next important property we should take a look onto set of points $\mathbf r$ for which $(\mathbf r, \mathbf a) = C$ for some fixed constant $C$. You can see that this set of points is exactly the set of points for which projection onto $\mathbf a$ is the point $C \cdot \dfrac{\mathbf a}{|\mathbf a|}$ and they form hyperplane orthogonal to $\mathbf a$. You can see vector $\mathbf a$ alongside with several vectors having same dot product with it in 2D on the picture below

<center>![Vectors having same dot product with a](https://i.imgur.com/eyO7St4.png)</center>

In 3D case such vectors will rather form plane than line. Note that this result allows us to define a line in 2D as $(\mathbf r, \mathbf n)=C$ or $(\mathbf r - \mathbf r_0, \mathbf n)=0$ where $\mathbf n$ is vector orthogonal to the line and $\mathbf r_0$ is any vector already present on the line and $C = (\mathbf r_0, \mathbf n)$. In 3D in the same manner plane can be defined.
## Cross product
### Definition
Assume you have three vectors $\mathbf a$, $\mathbf b$ and $\mathbf c$ in 3D space joined in parallelepiped as in the picture below:

<center>![Three vectors](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3e/Parallelepiped_volume.svg/240px-Parallelepiped_volume.svg.png)</center>

How would you calculate its volume? From school we know that we should multiply area of base and height, which is projection of $\mathbf a$ onto direction orthogonal to base. That means that if we define $\mathbf b \times \mathbf c=[\mathbf b, \mathbf c]$ as vector which is orthogonal to both $\mathbf b$ and $\mathbf c$ and which length is equal to area of parallelogram formed by $\mathbf b$ and $\mathbf c$ then $|(\mathbf a, \mathbf b, \mathbf c)| = |(\mathbf a,[\mathbf b,\mathbf c])|$ will be equal to the volume of parallelepiped. For integrity we will say that $[\mathbf b, \mathbf c]$ will be always directed in such way that rotation from vector $\mathbf b$ to vector $\mathbf c$ from the point of $[\mathbf b, \mathbf c]$ is always counter-clockwise (see the picture below)

<center>![cross product](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b0/Cross_product_vector.svg/250px-Cross_product_vector.svg.png)</center>

This defines cross (or vector) product $[\mathbf b, \mathbf c]$ of vectors $\mathbf b$ and $\mathbf c$ and triple product $(\mathbf a, \mathbf b, \mathbf c)$ of vectors $\mathbf a$, $\mathbf b$ and $\mathbf c$.

Some notable properties of cross and triple products:

1. $[\mathbf a, \mathbf b] = -[\mathbf b, \mathbf a]$
2. $[\alpha \cdot \mathbf a, \mathbf b] = \alpha [\mathbf a, \mathbf b]$
3. For any $\mathbf b$ and $\mathbf c$ there is exactly one vector $\mathbf r$ such that $(\mathbf a, \mathbf b, \mathbf c) = (\mathbf a, \mathbf r)$ for any vector $\mathbf a$. <br>Indeed if there are two such vectors $\mathbf r_1$ and $\mathbf r_2$ then $(\mathbf a, \mathbf r_1 - \mathbf r_2)=0$ for all vectors $\mathbf a$ which is possible only when $\mathbf r_1 = \mathbf r_2$.
3. $(\mathbf a, \mathbf b, \mathbf c) = (\mathbf b, \mathbf c, \mathbf a) = -(\mathbf a, \mathbf c, \mathbf b)$
3. $[\mathbf a + \mathbf b, \mathbf c] = [\mathbf a, \mathbf c] + [\mathbf b, \mathbf c]$. Indeed for all vectors $\mathbf r$ holds chain of equations $$(\mathbf r, [\mathbf a + \mathbf b, \mathbf c]) = (\mathbf r, \mathbf a + \mathbf b, \mathbf c) = (\mathbf a + \mathbf b, \mathbf c, \mathbf r) = (\mathbf a, \mathbf c, \mathbf r) + (\mathbf b, \mathbf c, \mathbf r) = (\mathbf r, \mathbf a, \mathbf c) + (\mathbf r, \mathbf b, \mathbf c) = (\mathbf r, [\mathbf a, \mathbf c] + [\mathbf b, \mathbf c])$$ Which proves $[\mathbf a + \mathbf b, \mathbf c] = [\mathbf a, \mathbf c] + [\mathbf b, \mathbf c]$ due to point 3.
3. $|[\mathbf a, \mathbf b]|=|\mathbf a| \cdot |\mathbf b| \sin \theta$ where $\theta$ is angle between $\mathbf a$ and $\mathbf b$, since $|[\mathbf a, \mathbf b]|$ equals to area of parallelogram formed by $\mathbf a$ and $\mathbf b$. 

Given all this and that for unit vectors holds

$$[\mathbf e_x, \mathbf e_x] = [\mathbf e_y, \mathbf e_y] = [\mathbf e_z, \mathbf e_z] = \mathbf 0, \\\
[\mathbf e_x, \mathbf e_y] = \mathbf e_z, [\mathbf e_y, \mathbf e_z] = \mathbf e_x, [\mathbf e_z, \mathbf e_x] = \mathbf e_y$$

We can calculate cross product of $\mathbf a = (x_1;y_1;z_1)$ and $\mathbf b = (x_2;y_2;z_2)$ in coordinate form:

$$[\mathbf a, \mathbf b] = [x_1 \cdot \mathbf e_x + y_1 \cdot \mathbf e_y + z_1 \cdot \mathbf e_z, x_2 \cdot \mathbf e_x + y_2 \cdot \mathbf e_y + z_2 \cdot \mathbf e_z] = \begin{matrix}\mathbf (y_1 z_2 - z_1 y_2)\mathbf e_x  \\\ (z_1 x_2 - x_1 z_2)\mathbf e_y \\\ (x_1 y_2 - y_1 x_2) \mathbf e_z\end{matrix} \begin{matrix} + \\\ + \\\ ~ \end{matrix}$$

Which also can be written in more elegant form

$$[\mathbf a, \mathbf b] = \begin{vmatrix}\mathbf e_x & \mathbf e_y & \mathbf e_z \\\ x_1 & y_1 & z_1 \\\ x_2 & y_2 & z_2 \end{vmatrix}, (\mathbf a, \mathbf b, \mathbf c) = \begin{vmatrix} x_1 & y_1 & z_1 \\\ x_2 & y_2 & z_2 \\\ x_3 & y_3 & z_3 \end{vmatrix}$$

Here $| \cdot |$ holds for determinant of matrix. 

Some kind of cross product (namely pseudo-scalar product) can be implemented in 2D case. If we would like to calculate area of parallelogram formed by vectors $\mathbf a$ and $\mathbf b$ we would compute $|(\mathbf e_z, [\mathbf a, \mathbf b])| = |x_1 y_2 - y_1 x_2|$. Another way to obtain the same result is to multiply $|\mathbf a|$ (base of parallelogram) with projection of vector $\mathbf b$ (height of parallelogram) onto vector $\mathbf a$ rotated by $90^\circ$ which is $\widehat{\mathbf a}=(-y_1;x_1)$. That is, to calculate $|(\widehat{\mathbf a},\mathbf b)|=|x_1y_2 - y_1 x_2|$. 

If we will take sign into consideration then it will be positive if rotation from $\mathbf a$ to $\mathbf b$ (i.e. from point of $\mathbf e_z$) is performed counter-clockwise and negative otherwise. That defines pseudo-scalar product. Note that it also equals $|\mathbf a| \cdot |\mathbf b| \sin \theta$ where $\theta$ is angle from $\mathbf a$ to $\mathbf b$ count counter-clockwise (i.e. negative if rotation is clockwise).

Let's implement all this stuff!

```cpp
point3d cross(point3d a, point3d b) {
    return point3d(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}
ftype triple(point3d a, point3d b, point3d c) {
    return dot(a, cross(b, c));
}
ftype cross(point2d a, point2d b) {
    return a.x * b.y - a.y * b.x;
}
```

### Properties
As for cross product, it equals zero vector iff vectors $\mathbf a$ and $\mathbf b$ are collinear. Same for triple product it equals zero iff vectors $\mathbf a$, $\mathbf b$ and $\mathbf c$ are complanar. From this we can obtain universal equations defining line and plane. Line can be defined via its direction vector $\mathbf d$ and initial point $\mathbf r_0$ or by two points $\mathbf a$ and $\mathbf b$. For first kind line is defined as $[\mathbf r - \mathbf r_0,\mathbf d]=0$ and for second it's $[\mathbf r - \mathbf a, \mathbf b - \mathbf a] = 0$. As for plane, it can be defined by three points $\mathbf a$, $\mathbf b$ and $\mathbf c$ as $(\mathbf r - \mathbf a, \mathbf b - \mathbf a, \mathbf c - \mathbf a)=0$ or by initial point $\mathbf r_0$ and two directions lying in this plane $\mathbf d_1$ and $\mathbf d_2$: $(\mathbf r - \mathbf r_0, \mathbf d_1, \mathbf d_2)=0$.

In 2D case pseudo-scalar product also may be used to check orientation between two vectors because it's positive if rotation from first to second is clockwise and negative otherwise. And, of course, in can be used to calculate areas of polygons which is described in other articles. Triple product can be used for same purposes in 3D space.

## Exercises

### Line intersection

There are many possible ways to define a line in 2D and you shouldn't hesitate to combine them. For example we have two lines and we want to find their intersection points. We can say that all points from first line can be parametrized as $\mathbf r = \mathbf a_1 + t \cdot \mathbf d_1$ where $\mathbf a_1$ is initial point, $\mathbf d_1$ is direction and $t$ is some real parameter. As for second line all its points must satisfy $[\mathbf r - \mathbf a_2, \mathbf d_2]=0$. From this we can easily find parameter $t$:

$$[\mathbf a_1 + t \cdot \mathbf d_1 - \mathbf a_2,\mathbf d_2]=0 \to t = \dfrac{[\mathbf a_2 - \mathbf a_1,\mathbf d_2]}{[\mathbf d_1, \mathbf d_2]}$$

Let's implement function to intersect two lines.

```cpp
point2d intersect(point2d a1, point2d d1, point2d a2, point2d d2) {
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}
```

### Planes intersection
However sometimes it might be hard to use some geometric insights. For example, you're given three planes defined by initial points $\mathbf a_i$ and directions $\mathbf d_i$ and you want to find their intersection point. You may note that you just have to solve system of equations:

$$\begin{cases}(\mathbf r, \mathbf n_1) = (\mathbf a_1, \mathbf n_1), \\\ (\mathbf r, \mathbf n_2) = (\mathbf a_2, \mathbf n_2), \\\ (\mathbf r, \mathbf n_3) = (\mathbf a_3, \mathbf n_3)\end{cases}$$

Instead of thinking on geometric approach, you can work out on algebraic one which can be obtained immediately. For example, given that you already implemented point class, it will be easy for you to solve this system using Cramer's rule because triple product is simply determinant of matrix obtained from vectors being its columns:
```cpp
point3d intersect(point3d a1, point3d n1, point3d a2, point3d n2, point3d a3, point3d n3) {
    point3d x(n1.x, n2.x, n3.x);
    point3d y(n1.y, n2.y, n3.y);
    point3d z(n1.z, n2.z, n3.z); 
    point3d d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return point3d(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}
```

Now you may try to find out approaches for common geometric operations yourself to get used to all this stuff!
