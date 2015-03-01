#ifndef MESSAGE_H
#define MESSAGE_H
#include <list>
#include "handle.h"
class Cell; 
class Message:public HandleSeed
{
    public:
        int Energy;
        int Style;
        int Delay;
        void operator= (Message& T);
        void Copy(Message *M);
        Message(int E,int S,int D):Energy(E),Style(S),Delay(D){}
        Message(Message& M);
        Message(const Message& M);
        Message(){}
};
void Message::Copy(Message *M)
{
    Energy=M->Energy;
    Style=M->Style;
    Delay=M->Delay;
}
 Message::Message(Message &M)
{
    Energy=M.Energy;
    Style=M.Style;
    Delay=M.Delay;
}
Message::Message(const Message &M)
{
    Energy=M.Energy;
    Style=M.Style;
    Delay=M.Delay;
}
void Message::operator=(Message &M)
{
    Energy=M.Energy;
    Style=M.Style;
    Delay=M.Delay;
}

#endif // MESSAGE_H
