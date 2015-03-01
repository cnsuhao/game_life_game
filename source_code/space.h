#ifndef SPACE_H
#define SPACE_H
#include "cell.h" 
class Space
{
    public:
        int E;
        int S;
        Handle<Cell> L;
        Space():E(0),S(0){}
};
#endif 
