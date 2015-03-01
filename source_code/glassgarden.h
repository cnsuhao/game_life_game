#ifndef CELL_GLASSGARDEN_H
#define CELL_GLASSGARDEN_H
#include <list>
#include <map>
#include <set>
#include "cell.h"
#include "space.h" 
#include "p.o/plugin_base.h"
class GlassGarden:public Plugin_Base
{
    public:
        bool Start;
        bool Draw;
        float XX;
        int CellNumber;
        std::list<Handle<Cell> > CellList;
        std::map<int,std::map<int,Space> > LiveSpace;
        bool FindRange(int x,int y,int R);
        //void Get(Message &Tc);
        void Get(Handle<Cell> P);
        void Run(void);
        bool Find(int x,int y);
        //bool Locate(int x,int y);
        void Show(ControlCenter *Data);
        void Analyze(ControlCenter *Data);
        GlassGarden():Plugin_Base("GG"),XX(20.0),Start(true),Draw(true){}
};
void GlassGarden::Show(ControlCenter *Data)
{
    for(std::list<Handle<Cell> >::iterator Po=CellList.begin();Po!=CellList.end();++Po)
    {
        if(*Po)
        {
            (*Po)->Show(this);
        }
    }
}
void GlassGarden::Analyze(ControlCenter *Data)
{
    if(Start)
        Run();
    while(!Library.empty())
    {
        Handle<Information> Te=GetInformation();
        if(Te)
        {
            if(Te->Category1==INFEVENT)
            {
                if(Te->Category2==INFKEY)
                {
                    if(Te->Category3==INFKEYDOWN)
                    {
                        if(Te->Data1.uc=='q')
                            XX*=2.0;
                        else if(Te->Data1.uc=='w')
                            XX/=2.0;
                        else if(Te->Data1.uc=='e')
                            Start=!Start;
                        else if(Te->Data1.uc=='r')
                        {
                            if(CellNumber>=500)
                                Draw=true;
                        }
                    }
                }
            }
        }
    }
}
void GlassGarden::Get(Handle<Cell> P)
{
    if(P)
    { 
	   CellList.push_back(P);
	   LiveSpace[P->X][P->Y].L=P;
	   CellNumber+=1;
    }
}
bool GlassGarden::FindRange(int x,int y,int Range)
{
    int T=Range*Range; 
    for(int i=-Range;i<=Range;++i)
    {
        for(int k=-Range;k<=Range;++k)
        {
            if(i*i+k*k<=T)
            {
                if(!(LiveSpace[x][y].L))
                {
                    return false; 
                } 
            } 
        }
    }
    return true;
}
bool GlassGarden::Find(int x,int y)
{
    if(LiveSpace[x][y].L)
        return true;
    return false;
}
void GlassGarden::Run(void)
{
    for(std::list<Handle<Cell> >::iterator Po=CellList.begin();Po!=CellList.end();++Po)
    {
        if(*Po)
        {
            (*Po)->Analyze(static_cast<void*>(this));
        }else{
            CellList.erase(Po--);
            CellNumber-=1;
        }
    }
}

#endif // GLASSGARDEN_H
