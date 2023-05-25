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

float Position::distance(Position p)
{
    return sqrt(pow(this->x - p.getX(), 2) + pow(this->y - p.getY(), 2));
}

bool Position::operator==(Position p)
{
    return (this->x == p.getX() && this->y == p.getY());
}

Position Position::operator+(Position p)
{
    return Position(this->x + p.getX(), this->y + p.getY());
}

Position Position::operator/(float f)
{
    return Position(this->x / f, this->y / f);
}