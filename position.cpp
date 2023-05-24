#include "position.h"

using namespace std;

// CONSTRUCTEURS
Position::Position()
{
    this->x = 0;
    this->y = 0;
}
Position::Position(float x, float y)
{
    this->x = x;
    this->y = y;
}


// DESTRUCTEURS
Position::~Position()
{
}


// METHODES
float Position::getX()
{
    return this->x;
}

float Position::getY()
{
    return this->y;
}

void Position::setX(float x)
{
    this->x = x;
}

void Position::setY(float y)
{
    this->y = y;
}

float Position::distance(Position p, Position q)
{
    return sqrt(pow(p.getX() - q.getX(), 2) + pow(p.getY() - q.getY(), 2));
}
