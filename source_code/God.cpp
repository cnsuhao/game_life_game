#include "p.o/controlcenter.h"
#include "glassgarden.h"
#include "normalcell.h"
#include "reacter.h"
#include <iostream>
#include <time.h>
//#include <time>
ControlCenter CC;
Handle<Plugin_Base> GG=new GlassGarden();
int main(int argc, char* argv[])
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);//指定混合模式
    glEnable(GL_BLEND);   // 打开混合模式
    srand(time(0));
    Handle<GlassGarden> Oi=GG;
    for(int i=0;i<10;++i)
    {
        Handle<Cell> Ty=new NorCell(0,i,1000,0,1000,0,0);
        Oi->Get(Ty);
    }
    //for(int k=0;k<30;++k)
        Handle<Cell> Pc=new Reacter(0,0);
        Oi->Get(Pc);
        Pc=new Reacter(0,19);
        Oi->Get(Pc);
    Oi.Unused();
    CC.Regedit(GG);
    CC.Init(1);
    while(CC.Running)
    {
        CC.Run();
        CC.Finish();
    }
    //std::cout<<"Finish!"<<std::endl;
}
