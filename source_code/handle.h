#ifndef DIY_HANDLE_H
#define DIY_HANDLE_H
#include <stdio.h>
class HandleSeed
{
    public:
    bool Exist;
    unsigned int Life;
    unsigned int Using;
    virtual ~HandleSeed(){}
    virtual bool CheckExist(){return Exist;}
    virtual void Destory(){Exist=false;}
    //virtual void Use()=0;
    HandleSeed():Exist(true),Life(0),Using(0){}
};


template <class T>


class Handle
{
    public:
        bool Used;
        T* Data;
        unsigned int Life;
        void operator =(T* L);
        bool operator ==(Handle& H);
        void operator =(Handle& H);
        void operator =(const Handle& H);
        template <class G>
            void operator =(Handle<G>& D);
        void Rebirth();
        void Follow(){if(Used) Life=Data->HandleSeed::Life;}
        void Unused();
        operator bool();
        bool Exist();
        operator T*(void){return Data;}
        T* operator->(){return Data;}
        template <class G>
            bool operator ==(Handle<G>&);
        template <class P>
                operator Handle<P>();
        Handle():Used(false){}
        Handle(const Handle& H);
        Handle(T*);
        virtual ~Handle();
};
template <class P>
bool Handle<P>::operator == (Handle<P>& F)
{
    if(*this)
    {
        if(F)
        {
            if(Data==F.Data)
                return true;
        }
    }
    return false;
}
template <class T>
template <class G>
void Handle<T>::operator =(Handle<G>& D)
{
    this->Unused();
    if(D)
    {
        T* P=dynamic_cast<T*>(D.Data);
        if(P!=NULL)
        {
            *this=P; 
        }
    }
}
template <class T>
template <class G>
Handle<T>::operator Handle<G>()
{
    Handle<G> Tem;
    if(*this)
    {
        G* P=dynamic_cast<G*>(Data);
        if(P!=NULL)
        {
            Tem=P;
        }
    }
    return Tem;
}
template<class T>
void Handle<T>::operator =(T* L)
{
    if(Used)
    {
        Data->HandleSeed::Using-=1;
        if(Data->HandleSeed::Using==0)
        {
            delete Data;
        }
    }else{
        Used=true;
    }
    Life=L->HandleSeed::Life;
    L->HandleSeed::Using+=1;
    Data=L;
}
template<class T>
void Handle<T>::operator =(Handle<T>& H)
{
    if(this!=&H)
    {
        if(Used)
        {
            Data->HandleSeed::Using-=1;
            if(Data->HandleSeed::Using==0)
            {
                delete Data;
            }
            Used=false;
        }
        Used=H.Used;
        Data=H.Data;
        Life=H.Life;
        if(H.Used)
        {
            Data->HandleSeed::Using+=1;
        }
    }
}
template<class T>
void Handle<T>::operator =(const Handle<T>& H)
{
    if(this!=&H)
    {
        if(Used)
        {
            Data->HandleSeed::Using-=1;
            if(Data->HandleSeed::Using==0)
            {
                delete Data;
            }
            Used=false;
        }
        Used=H.Used;
        Data=H.Data;
        Life=H.Life;
        if(H.Used)
        {
            Data->HandleSeed::Using+=1;
        }
    }
}
template<class T>
Handle<T>::Handle(const Handle &H)
{
    Used=H.Used;
    Data=H.Data;
    Life=H.Life;
    if(H.Used)
    {
        H.Data->HandleSeed::Using+=1;
    }
}
template<class T>
Handle<T>::~Handle()
{
    if(Used)
    {
        Data->HandleSeed::Using-=1;
        if(Data->HandleSeed::Using==0)
        {
            delete Data;
        }
    }
}
template<class T>
Handle<T>::Handle(T *L)
{
    Life=L->HandleSeed::Life;
    L->HandleSeed::Using+=1;
    Data=L;
    Used=true;
}
template<class T>
bool Handle<T>::Exist()
{
    if(!Used)
    {
        return false;
    }else{
        if(Life!=Data->HandleSeed::Life) return false;
        else return Data->CheckExist();
    }
}
template<class T>
Handle<T>::operator bool()
{
    return Exist();
}
template<class T>
void Handle<T>::Rebirth()
{
    if(Exist())
    {
        Data->HandleSeed::Life+=1;
        Life=Data->HandleSeed::Life;
    }
}
template <class T>
template <class G>
bool Handle<T>::operator ==(Handle<G>& P)
{
    if(*this)
    {
        if(P)
        {
            if(Data==dynamic_cast<T*>(P.Data))
            {
                return true;
            }
        }
    }
    return false;
}
template <class T>
void Handle<T>::Unused()
{
    if(Used)
    {
        Data->HandleSeed::Using-=1;
        if(Data->HandleSeed::Using==0)
        {
            delete Data;
        }
        Used=false;
    }
}
#endif // HANDLE_H
