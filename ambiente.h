#ifndef AMBIENTE_H
#define AMBIENTE_H
#include "movbro.h"
#include <vector>

using namespace std;

class ambiente
{
public:
    ambiente();
    void passaTempo();
    void criaAgentes(int quantidade);
    int getQuantAgentes() {return this->agentes.size();}
    double getPosXAg(int i);
    double getPosYAg(int i);
    double getHeadAg(int i);
    double getStepAg(int i);
    double getRaioAg(int i);
    void addVizAgUp(int i, MovBro *vz);
    void addVizAgDown(int i, MovBro *vz);
    int getNeig(int i);
    bool getHaveUpNe(int i);
    bool getHaveDownNe(int i);


    bool updatedAgent(int i);

    int getTamMundo() {return this->tamMundo;}
private:
    vector <MovBro> agentes;
    int tamMundo;
    void refreshPerception(int i);
    void worldModel(int i);
    double calcAng(double pix,double piy,double pjx,double pjy);

};

#endif // AMBIENTE_H
