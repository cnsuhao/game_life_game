#ifndef BEGINER_H
#define BEGINER_H
#include "glassgarden.h"
#include "normalcell.h"
class Beginer:public NorCell
{
public:
    void Produce(GlassGarden* GG);
    void Analyze(void *C);
    Biginer(int x,int y,long E):NorCell(x,y,E,0,0,0){}
};

#endif // BEGINER_H
