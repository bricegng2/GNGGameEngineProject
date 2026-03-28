
Here's a vec2 class with a limited subset of features, it doesn't correctly support const vec2 and has some questionable return types and parameter types on the operators.

```c++
    class vec2
    {
    public:
        vec2() {}
        vec2(float nxy) : x(nxy), y(nxy) {}
        vec2(float nx, float ny) : x(nx), y(ny) {}

        vec2 operator+(vec2 o) { return vec2(x + o.x, y + o.y); }
        vec2 operator*(float o) { return vec2(x * o, y * o); }
        void operator+=(vec2 o) { x += o.x; y += o.y; }

        float length() { return sqrt( x*x + y*y ); }
        float dot(vec2 o) { return x*o.x + y*o.y; }

        void normalize()
        {
            float len = length();
            if( len == 0 )
                return;
            x /= len;
            y /= len;
        }

    public:
        float x = 0;
        float y = 0;
    };
```

In C++, operator overrides often work with reference types, which allow for ugly code like the following:

```c++
float v1 = 1;
float v2 = 2;
float& v3 = v1 += v2;
```
