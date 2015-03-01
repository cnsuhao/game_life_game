#ifndef NORMALCELL_H
#define NORMALCELL_H
#include "cell.h"
#include "glassgarden.h"
#include <math.h>
class NorCell:public Cell
{
public:
    virtual void Analyze(void* C);
    virtual void Show(void* C);
    //void Target(GlassGarden *GG);
    void LiveActive(GlassGarden *GG);
    void TemTargetActive(GlassGarden *GG);
    void TargetActive(GlassGarden* GG);
    void DeliverMessage(GlassGarden* GG);
    void Produce(GlassGarden *GG);
    void Predation(GlassGarden* GG);
    NorCell(int x,int y,long e,int d,int l,int m,int i):Cell(x,y,e,d,l,m,i){}
};
void NorCell::Predation(GlassGarden* GG)
{
    for(int i=-2;i<=2;++i)
    {
        int u=abs(i);
        for(int k=u-2;k<=2-u;++k)
        {
            Space &Te=GG->LiveSpace[X+i][Y+k];
            int c=3-u-abs(k);
            if(Te.E>=c)
            {
                Te.E-=c;
                E+=c;
            }else if(Te.E>0)
            {
                E+=Te.E;
                Te.E=0;
            }
        }
    }
}
void NorCell::Show(void *C)
{
#ifdef DIY_CONTROLCENTER_H
    GlassGarden *GG=static_cast<GlassGarden*>(C);
    //if(GG->CellNumber<=50)
    //{
        glColor4f(0.5,0.5,0.5,0.5);
        glBegin(GL_LINE_LOOP);
        glVertex2f(X-0.2,Y-0.2;
        glVertex2f(X-0.2,Y+0.2);
        glVertex2f(X+0.2,Y+0.2);
        glVertex2f(X+0.2,Y-0.2);
        glEnd();
    //}
    glBegin(GL_LINES);
    if(Target)
    {
        glColor4f(1.0,0.0,0.0,0.5);
        glVertex2f(X/GG->XX,Y/GG->XX);
        glVertex2f(Target->X/GG->XX,Target->Y/GG->XX);
    }
    if(TemTarget)
    {
        glColor4f(0.0,0.0,1.0,0.5);
        glVertex2f(X/GG->XX,Y/GG->XX);
        glVertex2f(TemTarget->X/GG->XX,TemTarget->Y/GG->XX);
    }
    if(Son)
    {
            glColor4f(0.0,1.0,0.0,0.5);
            glVertex2f(X/GG->XX,Y/GG->XX);
            glVertex2f(Son->X/GG->XX,Son->Y/GG->XX);
    }
    glEnd();
#endif
}
void NorCell::Produce(GlassGarden* GG)
{
    int x,y;
    x=rand()%11;
    y=rand()%11;
    x-=5;
    y-=5;
    if(!GG->Find(X+x,Y+y))
    {
        E-=10;
        Handle<Cell> Po=new NorCell(X+x,Y+y,E/2,D,L.NeedTime,MC,IC);
        if(Target)
        {
            Son=Po;
            Soon=0;
        }else{
            Target=Po;
        }
        E=E/2;
        GG->Get(Po);
    }else{
        E-=1;
    }
}
void NorCell::DeliverMessage(GlassGarden *GG)
{
    if(!ML.empty())
    {
        long AllEnergy=0;
        int AllStyle=0;
        long Want;
        int Size=0;
        int Num=0;
        if(E<10) Want=50;
        else if(E<30) Want=20;
        else Want=10;
        std::list<Message >::iterator Po;
        for(Po=ML.begin();Po!=ML.end();++Po)
        {
            AllEnergy+=Po->Energy;
            if(AllStyle==SM)
            {
                AllStyle+=Po->Style*10;
                Size+=10;
            }else{
                AllStyle+=Po->Style;
                Size+=1;
            }
        }
        if(AllEnergy>=Want)
        {
            AllEnergy-=Want;
            E+=Want;
            //AllEnergy=AllEnergy*0.7;
            AllStyle/=Size;
            //Message Tem(AllEnergy,AllStyle,D,Target);
            //GG->Get(Tem);
            E-=10;
            if(Target){Num+=1;}
            if(TemTarget){Num+=1;}
            if(Son){Num+=1;}
            if(Num==0)
            {
                E+=AllEnergy;
            }else{
                if(Target)
                {
                    Message M(AllEnergy/Num,AllStyle,D);
                    Target->Get(M);
                }
                if(TemTarget)
                {
                    Message M(AllEnergy/Num,AllStyle,D);
                    TemTarget->Get(M);
                }
                if(Son)
                {
                    Message M(AllEnergy/Num,AllStyle,D);
                    Son->Get(M);
                }
            }
        }else{
            E+=AllEnergy;
        }
        ML.clear();
    }
}

void NorCell::TemTargetActive(GlassGarden *GG)
{
    if(TemTarget)
    {
        TemTar+1l;
        if(TemTar)
        {
            TemTarget.Unused();
        }
    }else{
        int x,y;
        int P=0;
        while((!(TemTarget))&&P<5)
        {
        x=rand()%11;
        y=rand()%11;
        x-=5;
        y-=5;
        if(GG->FindRange(X,Y,5))
        {
            if(GG->Find(X+x,Y+y))
            {
                for(std::list<Handle<Cell> >::iterator Po=GG->CellList.begin();Po!=GG->CellList.end();++Po)
                {
                    if(*Po)
                    {
                        if(!((*Po)==Target))
                        {
                            if((*Po)->X==X+x&&(*Po)->Y==Y+y)
                            {
                                TemTarget=*Po;
                                TemTar=0;
                            }
                        }
                    }
                }
            }
            E-=5;
        }else{
            //E-=1;
        }
        P+=1;
        }
    }
}

void NorCell::TargetActive(GlassGarden *GG)
{
    int P=0;
    while((!(Target))&&P<5)
    {
        int x,y;
        x=rand()%11;
        y=rand()%11;
        x-=5;
        y-=5;
        if(GG->FindRange(X,Y,5))
        {
            if(GG->Find(X+x,Y+y))
            {
                for(std::list<Handle<Cell> >::iterator Po=GG->CellList.begin();Po!=GG->CellList.end();++Po)
                {
                    if(*Po)
                    {
                        if(!((*Po)==TemTarget))
                        {
                            if((*Po)->X==X+x&&(*Po)->Y==Y+y)
                            {
                                Target=*Po;
                            }
                        }
                    }
                }
            }
            E-=9;
        }
        P+=1;
    }
    //E-=1;
}

void NorCell::LiveActive(GlassGarden *GG)
{
    L+1l;
    if(L||E<=0)
    {
        //GG->Remove(this);
        Destory();
    }
}

void NorCell::Analyze(void *C)
{
    GlassGarden* GG=static_cast<GlassGarden*>(C);
    LiveActive(GG);
    Predation(GG);
    //DeliverMessage(GG);
    if(E>=100)
    {
        Produce(GG);
    }
    Soon+1l;
    if(Soon)
    {
        Son.Unused();
    }
    if(TemTarget)
    {
        if(TemTarget->E<E)
        {
            int c=E-TemTarget->E;
            TemTarget->E+=c*0.2;
            E-=c*0.3;
        }
    }
    if(Target)
    {
        if(Target->E<E)
        {
            int c=E-Target->E;
            Target->E+=c*0.2;
            E-=c*0.3;
        }
    }
    TemTargetActive(GG);
    //TargetActive(GG);
}

#endif // NORMALCELL_H
