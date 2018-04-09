#include "movbro.h"
#include <stdlib.h>
#include <math.h>
#define PI 3.1416

double MovBro::getX()
{
    return this->x;
}

const double MovBro::getY()
{
    return y;
}

double MovBro::getHead() const
{
    return head;
}

double MovBro::getStep() const
{
    return step;
}

void MovBro::addVizUp(MovBro *vz)
{
    if(haveUpNe || vz->haveDownNe)
        return;
    this->upNe=vz;
    this->haveUpNe=true;
    this->inside=true;
    vz->downNe=this;
    vz->haveDownNe=true;
    vz->inside=true;
}
void MovBro::addVizDown(MovBro *vz)
{
    if(haveDownNe || vz->haveUpNe)
        return;
    this->downNe=vz;
    this->haveDownNe=true;
    this->inside=true;
    vz->upNe=this;
    vz->haveUpNe=true;
    vz->inside=true;
}


double MovBro::getVx() const
{
    return vx;
}

double MovBro::getVy() const
{
    return vy;
}


int MovBro::getId() const
{
    return id;
}

double MovBro::getRaioViz() const
{
    return raioViz;
}

bool MovBro::getHaveUpNe() const
{
    return haveUpNe;
}

bool MovBro::getHaveDownNe() const
{
    return haveDownNe;
}

bool MovBro::getUpdated() const
{
    return updated;
}

void MovBro::setUpdated(bool value)
{
    updated = value;
}

void MovBro::escolhaVel()
{
    float r;
    r=(float)rand()/RAND_MAX;
    this->vx=r*this->step-this->step/2;
    r=(float)rand()/RAND_MAX;
    this->vy=r*this->step-this->step/2;
}

void MovBro::escolhaVelM(int n)
{
    float r;
    r=(double)rand()/RAND_MAX;
    double dh= r*this->dhead-this->dhead/2;
    this->head+=((double)dh/n);
    if(head>=360) head-=360;
    if(head<0) head+=360;
    this->escolhaVel();
    this->vx/=n;
    this->vy/=n;
}

void MovBro::runModel()
{
    if(this->inside)
        runModelInside();
    else
        runModelOutside();

    this->updated=true;
}

void MovBro::runModelOutside()
{
    this->escolhaVelM(1);
}

void MovBro::runModelInside()
{
    MovBro *pAgent=this,*pCM;
    int nP=1;
    while(pAgent->haveUpNe) // Go to the head of the polimer
        pAgent=pAgent->upNe;
    while(pAgent->haveDownNe) // count numbre of nucleotides
    {
        pAgent=pAgent->downNe;
        nP++;
    }
    for(int i=0;i<nP/2;i++) // Go to the midle of the polimer (center of mass)
        pAgent=pAgent->upNe;
    pCM=pAgent;
    pAgent->escolhaVelM(nP/2);
    // refresh the down half of the polimer
    while(pAgent->haveDownNe)
    {
        double pix,piy,dx,dy,st,d;
        pAgent=pAgent->downNe;
        pix=pAgent->upNe->x;
        piy=pAgent->upNe->y;
        st=0.005;
        d=(pAgent->upNe->head-90)*PI/180;
        dx=2*st*cos(d);
        dy=2*st*sin(d);
        pAgent->x=pix+dx;
        pAgent->y=piy+dy;
        pAgent->vx=pAgent->vy=0;
        pAgent->head=pAgent->upNe->head+3*pAgent->step*((double)rand()/RAND_MAX)-(3*pAgent->step/2);

        pAgent->updated=true;
    }
    // refresh the up half of the polimer
    pAgent=pCM;
    while(pAgent->haveUpNe)
    {
        double pix,piy,dx,dy,st,d;
        pAgent=pAgent->upNe;
        pix=pAgent->downNe->x;
        piy=pAgent->downNe->y;
        st=0.005;
        d=(pAgent->downNe->head+90)*PI/180;
        dx=2*st*cos(d);
        dy=2*st*sin(d);
        pAgent->x=pix+dx;
        pAgent->y=piy+dy;
        pAgent->vx=pAgent->vy=0;
        pAgent->head=pAgent->downNe->head+3*pAgent->step*((double)rand()/RAND_MAX)-(3*pAgent->step/2);

        pAgent->updated=true;
    }
    //pHead->step/=(N/2.0);
    //pHead->dhead/=((double)N/2.0);
}



void MovBro::move()
{
    this->x+=this->vx;
    this->y+=this->vy;
    // condições de contorno perodicas Modelo de mundo
    if(this->x>1)this->x=1;
    if(this->x<0)this->x=0;
    if(this->y>1)this->y=1;
    if(this->y<0)this->y=0;

}

MovBro::MovBro()
{
    static int lastId=0;
    this->id=++lastId;
    this->x=(double)rand()/RAND_MAX;
    this->y=(double)rand()/RAND_MAX;
    this->haveDownNe=false;
    this->haveUpNe=false;
    this->vx=0;
    this->vy=0;
    this->dir=0;
    this->head=(double)rand()/RAND_MAX*360;
    this->dhead=5;
    this->at=40;
    this->step=0.005;
    this->raioViz=10;
    this->updated=false;
    this->inside=false;
}

