#include "Block.h"

class Portal : public Block
{
    public:
        explicit Portal(int x, int y, bool pc, bool vertOrHoriz);
        int getX();
        int getY();
        //int getNewX();
        //int getNewY();
        int getHeight();
        int getWidth();
        void setX(int x);
        void setY(int y);
        void setHeight(int h);
        void setWidth(int w);
        void setColorR(Uint8 color);
        void setColorG(Uint8 color);
        void setColorB(Uint8 color);
        void setColorA(Uint8 color);
        Uint8 getColorR();
        Uint8 getColorG();
        Uint8 getColorB();
        Uint8 getColorA();
        void toggleClick();
        //void update();

//        void draw();

    private:
        int xLoc;
        int yLoc;
        //int newXLoc;
        //int newYLoc;
        int height;
        int width;
        Uint8 red;
        Uint8 blue;
        Uint8 green;
        Uint8 alpha;
        bool isActive;
        bool portalColor; // blue == 0 | orange == 1
};