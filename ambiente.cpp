#include "ambiente.h"
#include <math.h>

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}


ambiente::ambiente()
{
    int inutil=0;
    this->tamMundo=100; // metros
    this->criaAgentes(400);
}

void ambiente::passaTempo()
{
    int tam=this->agentes.size();
    for(int i=0; i<tam;i++)
    {
        if(!this->updatedAgent(i))
            this->refreshPerception(i);
        this->worldModel(i);
        this->agentes[i].move();
    }
    for(int i=0; i<tam;i++)
        this->agentes[i].setUpdated(false);
}

void ambiente::criaAgentes(int quantidade)
{
    for(int i=0;i<quantidade;i++)
    {
        MovBro aux;
        this->agentes.push_back(aux);
    }
}

double ambiente::getPosXAg(int i)
{
    return this->agentes[i].getX()*this->tamMundo;
}

double ambiente::getPosYAg(int i)
{
    return this->agentes[i].getY()*this->tamMundo;
}

double ambiente::getHeadAg(int i)
{
    return this->agentes[i].getHead();
}

double ambiente::getStepAg(int i)
{
    return this->agentes[i].getStep();
}

double ambiente::getRaioAg(int i)
{
    return this->agentes[i].getRaioViz()*this->agentes[i].getStep()*this->tamMundo;
}

void ambiente::addVizAgUp(int i,MovBro *vz)
{
    this->agentes.at(i).addVizUp(vz);
}

void ambiente::addVizAgDown(int i,MovBro *vz)
{
    this->agentes.at(i).addVizDown(vz);
}

int ambiente::getNeig(int i)
{
    if(this->agentes.at(i).getHaveUpNe() && !this->agentes.at(i).getHaveDownNe())
        return 1;
    if(!this->agentes.at(i).getHaveUpNe() && this->agentes.at(i).getHaveDownNe())
        return 2;
    if(this->agentes.at(i).getHaveUpNe() && this->agentes.at(i).getHaveDownNe())
        return 3;
    return 0;
}

bool ambiente::getHaveUpNe(int i)
{
    return this->agentes.at(i).getHaveUpNe();
}

bool ambiente::getHaveDownNe(int i)
{
    return this->agentes.at(i).getHaveDownNe();
}

bool ambiente::updatedAgent(int i)
{
    return this->agentes[i].getUpdated();
}

void ambiente::refreshPerception(int i)
{
    double pjx,pjy,pix,piy,dx,dy,st,d,raio,headI,headJ;
    int tam=this->agentes.size();
    pix=this->getPosXAg(i);
    piy=this->getPosYAg(i);
    st=this->getStepAg(i);
    raio=this->getRaioAg(i);
    headI=this->getHeadAg(i);
    for(int j=0; j<tam;j++)
    {
        if(i==j) continue;
        pjx=this->getPosXAg(j);
        pjy=this->getPosYAg(j);
        headJ=this->getHeadAg(j);
        dx=pix-pjx;
        dy=piy-pjy;
        d=sqrt(dx*dx+dy*dy);
        if(d<=raio && fabs(headI-headJ)<3 )
        {
            double a=this->calcAng(pix,piy,pjx,pjy);
            if(fabs(fabs(a-headI)-90)<10)
            {
                if((headI-a)>0)
                    this->addVizAgDown(i,&this->agentes[j]);
                else
                    this->addVizAgUp(i,&this->agentes[j]);

            }
        }
    }
}

void ambiente::worldModel(int i)
{
    this->agentes[i].runModel();
}

double ambiente::calcAng(double pix, double piy, double pjx, double pjy)
{
    double a=atan2(pjy-piy,pjx-pix)*180/3.1416;
    return a;
}
