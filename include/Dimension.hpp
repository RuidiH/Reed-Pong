#ifndef DIMENSION_HPP
#define DIMENSION_HPP

class Dimension
{
public:
    Dimension(int xPos, int yPos, int width, int height)
    {
        x = xPos;
        y = yPos;
        w = width;
        h = height;
    }

    int x;
    int y;
    int w;
    int h;
};

#endif