#ifndef CELL_CELL_H
#define CELL_CELL_H
#include "p.o/handle.h"
#include "p.o/calculate.h"
#include "message.h" 
#define PRODUCERANGE 5
#include <list>
enum CellAM
{
    CELL_FZ,
    CELL_NOR
};
class Cell:public HandleSeed
{
    public:
        int X;//Location X
        int Y;//Location Y
        long E;//Energy
        CellAM AM;//ActiveMode
        int D;//Delay
        int SM;//SpecialMessage
        Calculate L;
        int MC;//MessageChange
        int IC;//Itselfchange
        Handle<Cell> Target;
        Calculate TemTar;
        Calculate Soon;
        Handle<Cell> TemTarget;
        Handle<Cell> Son;
        std::list<Message > ML;
        void Get(Message M);
        virtual void Show(void* C){} 
        virtual void Analyze(void* C){ML.clear();}
        Cell(int x,int y,long e,int d,int l,int m,int i):X(x),Y(y),E(e),AM(CELL_NOR),D(d),L(l),MC(m),IC(i),TemTar(200),Soon(1000){}
        ~Cell(){}
};
void Cell::Get(Message T)
{
    ML.push_back(T); 
} 
#endif
