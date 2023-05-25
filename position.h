#ifndef _POSITION_H
#define _POSITION_H

#include <math.h>


class Position {

private:
    
    float x;
    float y;

public:

    // CONSTRUCTEURS
    Position();
    Position(float x, float y);

    // DESTRUCTEURS
    ~Position();

    // METHODES
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);

    float distance(Position p);

    bool operator==(Position p);

    Position operator+(Position p);

    Position operator/(float f);

};






#endif // _POSITION_H