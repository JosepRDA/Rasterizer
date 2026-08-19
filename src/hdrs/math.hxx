#pragma once

#include <cmath>
#include <initializer_list>

template<int size>
struct Vector {
public:
    // declaring them here bcoz i can't figure out how to the declare in the impl file
    float operator[](int index)
    {
        static_assert(index > 0 && index <=size, "Out of range index");

        return vec[index];
    }

    Vector<size> operator+(Vector<size>& other) 
    {
        for (int i = 0; i < size; i++)
            vec[i] += other[i];
    }

    Vector<size> operator-(Vector<size>& other) 
    {
        for (int i = 0; i < size; i++)
            vec[i] += other[i];
    }

    Vector<size> operator*(Vector<size>& other) 
    {
        for (int i = 0; i < size; i++)
            vec[i] *= other[i];
    }

    Vector<size> operator/(Vector<size>& other) 
    {
        for (int i = 0; i < size; i++)
            vec[i] /= other[i];
    }

    bool operator==(Vector<size>& other) 
    {
        for (int i = 0; i < size; i++)
            if(vec[i] != other[i])
                return false;

        return true;
    }

    Vector(std::initializer_list<float> items)
    {
        static_assert(items.size() == size, "Initializer list and template\
            parameter diverge in size (int x != int y)");

        vec = items; // works?
    }

    float lenth() const 
    {
        float len = 0.0f;
        for (int i = 0; i < size; i++) {
            len += std::sqrt(vec[i]);
        }
        return len;
    }

    Vector() = delete;
private:
    float vec[size];
};

using Vector2 = Vector<2>;
using Vector3 = Vector<3>;
using Vector4 = Vector<4>;

struct Triangle {
private:
    Vector3 vertices[3];
};

struct Mat4 {
private:
    float mat[16];
};

