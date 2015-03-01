#ifndef REACTER_H
#define REACTER_H
#include "normalcell.h"
#include "space.h"
class Reacter:public NorCell
{
public:
    float Time;
    long Energy;
    void Analyze(void *V);
    void Show(void *C);
    Reacter(int x,int y):NorCell(x,y,0,0,0,0,0),Energy(1000){}
};
void Reacter::Analyze(void *V)
{
    Time+=0.1;
    GlassGarden* GG=static_cast<GlassGarden*>(V);
    //TargetActive(GG);
    //TemTargetActive(GG);
    for(int i=-10;i<=10;++i)
    {
        int u=abs(i);
        for(int k=u-10;k<=10-u;++k)
        {
            if(i!=0||k!=0)
            {
                Space &Te=GG->LiveSpace[X+i][Y+k];
                if(Te.E<=1000)
                    Te.E+=(int)(1000-(u+abs(k))*100)*sin(Time)*sin(Time);
            }
        }
    }
}

void Reacter::Show(void *C)
{
#ifdef DIY_CONTROLCENTER_H
    GlassGarden *GG=static_cast<GlassGarden*>(C);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(X,Y+0.2);
    glVertex2f(X-0.2,Y-0.2);
    glVertex2f(X+0.2,Y-0.2);
    glEnd();
    glBegin(GL_LINES);
    if(Target)
    {
        glColor4f(1.0,0.0,0.5,0.5);
        glVertex2f(X/GG->XX,Y/GG->XX);
        glVertex2f(Target->X/GG->XX,Target->Y/GG->XX);
    }
    if(TemTarget)
    {
        glColor4f(1.0,0.5,0.1,0.5);
        glVertex2f(X/GG->XX,Y/GG->XX);
        glVertex2f(TemTarget->X/GG->XX,TemTarget->Y/GG->XX);
    }
    glEnd();
#endif
}

#endif // REACTER_H
