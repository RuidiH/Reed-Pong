#ifndef VECTOR2_HPP
#define VECTOR2_HPP

class Vector2 {
    public:
        void Set(int xPos, int yPos) {
            x = xPos;
            y = yPos;
        }

        int x;
        int y;
};

#endif