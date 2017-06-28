#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include "filexml.h"
#include <iostream>
using std::cerr;
using std::endl;


template <class T>
class Container{
    friend class Iteratore;
    friend class IteratoreConst;
private:

    class file{
    public:
       T info;
       file* next;
       file* prev;
       file(const T &i=T(), file* n=0, file* p=0);
       file(const file& f);
       ~file();
    };

    file* first;
    file* last;
    unsigned int dim;
    int RiempiDaLista(const filexml &, const string& tagname);
    void copia(file *primo);
public:
    Container();
    Container(const Container & c);
    Container& operator=(const Container& c);
    ~Container();
    T& operator[](unsigned int) const;
    T *primo() const;
    T *ultimo() const;
    int size() const;
    list<T *> TuttiFile() const;
    void AddFileDaLista(const string& pathRefAFileXML, const string& tagname);
    void AddFileDaLista(const filexml& f, const string& tagname);
    T& push_back(const T& f);
    T &push_back(string path);
    class Iteratore{
    public:
        file* p;
        Iteratore();
        Iteratore& operator++();
        Iteratore operator ++(int)const;
        Iteratore& operator--();
        Iteratore operator --(int)const;
        T& operator*()const;
        T* operator->()const;
        bool operator!= (const Iteratore&) const;
        bool operator==(const Iteratore&)const;

    };
    class IteratoreConst{
    public:
        const file* p;
        IteratoreConst();
        IteratoreConst& operator++();
        IteratoreConst operator ++(int)const;
        IteratoreConst& operator--();
        IteratoreConst operator --(int)const;
        const T& operator*()const;
        const T* operator->()const;
        bool operator!= (const IteratoreConst&) const;
        bool operator==(const IteratoreConst&)const;

    };


    Iteratore begin();
    Iteratore end();
    IteratoreConst begin()const;
    IteratoreConst end()const;

  };



#endif // CONTAINER_H

template <class T>
Container<T>::file::file(const T& i, Container<T>::file *n, Container<T>::file *p):info(i),next(n), prev(p){}

template<class T>
Container<T>::file::file(const Container<T>::file &f): info(f.info),next(f.next),prev(f.prev){}

template<class T>
Container<T>::file::~file()
{
    if(next)
        delete next;
}


template<class T>
Container<T>::Container():first(0), last(0), dim(0){}

template<class T>
Container<T>::Container(const Container<T> &c):first(0), last(0), dim(c.dim)
{
    copia(c.first);
}
template<class T>
Container<T> &Container<T>::operator=(const Container<T> &c)
{
    if(this != &c){
        if(first)
            delete first;
        first=0;
        last=0;
        copia(c.first);
        dim=c.dim;
    }
    return *this;
}
template<class T>
Container<T>::~Container()
{

    if(first){
        delete first;
    }
}

template<class T>
int Container<T>::RiempiDaLista(const filexml& f, const string &tagname)
{
    int conta=0;

        list<string> l= f.daiTestoDiNodi(tagname);

        for( list<string>::const_iterator it=l.begin(); it != l.end(); ++it){
            if(!first){
            first=last=new file(T(*it));
            }
            else{
            last->next= new file(T(*it),0, last);
            last=last->next;
            }
            ++conta;
            }
    return conta;
}
template <class T>
void Container<T>::copia(file* primo)
{
    if(primo){
        first=last=new file(primo->info);
        while(primo->next){
            primo=primo->next;
            last->next= new file(primo->info,0, last);
            last=last->next;
        }
    }
}
template<class T>
T & Container<T>::operator[](unsigned int i) const{

    if(i>=dim)
        throw string("indice fuori bound");

    file* temp= first;
    bool esci =false;
    for (unsigned int j=0; j<dim && !esci; ++j){
        if(j==i)
            esci=true;
        else
        temp=temp->next;
    }

    return (temp->info);
}


template<class T>
T *Container<T>::primo() const
{
    return &(first->info) ;
}
template<class T>
T *Container<T>::ultimo() const
{
    return &(last->info);
}
template<class T>
int Container<T>::size() const
{
    return dim;
}
template<class T>
list<T *> Container<T>::TuttiFile() const
{
    list<T*> l;

        file* temp=first;
        for(unsigned int i=0; i<dim; i++)
          {
            l.push_back(&(temp->info));
            temp=temp->next;
             }

return l;

}

template<class T>
void Container<T>::AddFileDaLista(const string& pathRefAFileXML, const string& tagname) try
{
    filexml f(pathRefAFileXML);
    if(! f.apriFile())
        throw f.daiErrore();
    else{
        dim=RiempiDaLista(f, tagname);
    }
}
catch(const string& err){
    cerr<<err<<endl;
}
template<class T>
void Container<T>::AddFileDaLista(const filexml &f, const string& tagname) try
{
    if(! f.apriFile())
        throw f.daiErrore();
    else{
        dim=RiempiDaLista(f, tagname);
    }
}
catch(string err){
    cerr<<err<<endl;
}
template<class T>
T &Container<T>::push_back(const T &f)
{
    if(!first)
        first=last=new file(f);
    else{
        last->next=new file(f,0,last);
        last=last->next;
    }
    ++dim;
    return f;

}

template<class T>
T& Container<T>::push_back(string path)
{
    if(!first){
        first=last=new file(T(path));
        ++dim;
        return first->info;
    }
    else{
        last->next=new file(T(path),0,last);
        last=last->next;
        ++dim;
        return last->info;
    }
}
template <class T>
typename Container<T>::Iteratore Container<T>::begin()
{
    Iteratore temp;
    temp.p=first;
    return temp;
}
template <class T>
typename Container<T>::Iteratore Container<T>::end()
{
    Iteratore temp;
    return temp;
}
template <class T>
typename Container<T>::IteratoreConst Container<T>::begin() const
{
    IteratoreConst temp;
    temp.p=first;
    return temp;
}
template <class T>
typename Container<T>::IteratoreConst Container<T>::end() const
{
    IteratoreConst temp;
    return temp;
}

template<class T>
Container<T>::Iteratore::Iteratore():p(0){}
template <class T>
typename Container<T>::Iteratore & Container<T>::Iteratore::operator++()
{
    if(p)
        p=p->next;
    return *this;
}
template <class T>
typename Container<T>::Iteratore Container<T>::Iteratore::operator ++(int) const
{
    Iteratore temp;
    if(p){
        temp.p=p;
        p=p->next;
    }
    return temp;
}

template <class T>
typename Container<T>::Iteratore & Container<T>::Iteratore::operator--()
{
    if(p)
        p=p->prev;
    return *this;
}
template <class T>
typename Container<T>::Iteratore Container<T>::Iteratore::operator --(int) const
{   Iteratore temp;
    if(p){
        temp.p = p;
        p=p->prev;
    }
    return temp;

}

template <class T>
T & Container<T>::Iteratore::operator*()const
{
    return p->info;
}
template <class T>
T* Container<T>::Iteratore::operator->() const
{
    return &(p->info);
}
template <class T>
bool Container<T>::Iteratore::operator!=(const Iteratore& i) const
{
    return !(p==i.p);
}
template <class T>
bool Container<T>::Iteratore::operator==(const Iteratore& i) const
{
    return p==i.p;
}

template<class T>
Container<T>::IteratoreConst::IteratoreConst():p(0){}
template <class T>
typename Container<T>::IteratoreConst & Container<T>::IteratoreConst::operator++()
{
    if(p)
        p=p->next;
    return *this;
}
template <class T>
typename Container<T>::IteratoreConst Container<T>::IteratoreConst::operator ++(int) const
{
    IteratoreConst temp;
    if(p){
        temp.p=p;
        p=p->next;
    }
    return temp;
}

template <class T>
typename Container<T>::IteratoreConst & Container<T>::IteratoreConst::operator--()
{
    if(p)
        p=p->prev;
    return *this;
}
template <class T>
typename Container<T>::IteratoreConst Container<T>::IteratoreConst::operator --(int) const
{   IteratoreConst temp;
    if(p){
        temp.p=p;
        p=p->prev;
    }
    return temp;

}

template <class T>
const T & Container<T>::IteratoreConst::operator*()const
{
    return p->info;
}
template <class T>
const T* Container<T>::IteratoreConst::operator->() const
{
    return &(p->info);
}
template <class T>
bool Container<T>::IteratoreConst::operator!=(const IteratoreConst& i) const
{
    return !(p==i.p);
}
template <class T>
bool Container<T>::IteratoreConst::operator==(const IteratoreConst& i) const
{
    return p==i.p;
}
