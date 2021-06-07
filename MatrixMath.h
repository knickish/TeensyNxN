#pragma once

#include <Arduino.h>

class MatrixMath
{
    public:
    float * vals;
    int size;

    MatrixMath(float * floats, int len)
    :vals(floats)
    ,size(len)
    {
    }

    bool invert_two()
    {
        if (size!=4)
        {
            return false;
        }

        float a, b, c, d;
        a = vals[0];
        b = vals[1];
        c = vals[2];
        d = vals[3];
        float det = (a*d)-(b*c);
        if (det)
        {
            vals[0] = d/det;
            vals[1] = -b/det;
            vals[2] = -c/det;
            vals[3] = a/det;
            return true;
        }
        else
        {
            return false;
        }
    }
};