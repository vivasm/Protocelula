#ifndef MOVBRO_H
#define MOVBRO_H

class MovBro
{
private:
    double x,y,vx,vy;
    double dir;
    double head;
    double dhead;
    double at;
    double step;
    bool haveUpNe;      // flag indicating that have up neighbor
    bool haveDownNe;    // flag indicating that have Down neighbor
    double raioViz;
    int id;
    bool inside;        // flag indicating the agent is inside a polimer
    bool updated;
    MovBro *upNe;       // point do upper neighbor (Lista encadeada)
    MovBro *downNe;
    void escolhaVel();
    void escolhaVelM(int n);
    void runModelInside();
    void runModelOutside();


public:
    void move();
    MovBro();

    double getX();
    const double getY() ;
    double getHead() const;
    double getStep() const;
    void addVizUp(MovBro *vz);
    void addVizDown(MovBro *vz);
    double getVx() const;
    double getVy() const;
    void runModel();
    int getId() const;
    double getRaioViz() const;
    bool getHaveUpNe() const;
    bool getHaveDownNe() const;
    bool getUpdated() const;
    void setUpdated(bool value);
};

#endif // MOVBRO_H

