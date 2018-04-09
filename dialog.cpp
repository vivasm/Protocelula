#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QGraphicsEllipseItem>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->tic= new QTimer();
        // conectando emissor e receptor do sinal
    connect(this->tic,SIGNAL(timeout()),this,SLOT(roda()));
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMaximizeButtonHint;
    setWindowFlags( flags );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonRoda_clicked()
{
   //this->roda();
   this->tic->start(10);
}

void Dialog::roda()
{
    this->amb.passaTempo();
    this->repaint();
}

void Dialog::paintEvent(QPaintEvent *e)
{
    QPainter estojo;

    estojo.begin(this);

    int Tjx=this->geometry().width();
    int Tjy=this->geometry().height();
    double fX=(double)Tjx/this->amb.getTamMundo();
    double fY=(double)Tjy/this->amb.getTamMundo();
    for(int i=0;i<this->amb.getQuantAgentes();i++)
    {
       double px=this->amb.getPosXAg(i);
       double py=this->amb.getPosYAg(i);
       if(!this->amb.getHaveUpNe(i) && this->amb.getHaveDownNe(i))
            estojo.setBrush(QColor(255,0,255));
       else if (!this->amb.getHaveDownNe(i) && this->amb.getHaveUpNe(i))
            estojo.setBrush(QColor(0,0,255));
       else
            estojo.setBrush(QColor(0,255,0));


       estojo.save();
       estojo.translate(px*fX,py*fY);
//       estojo.setBrush(QColor(0,0,255,20));
//       double raio=this->amb.getRaioAg(i);
//       estojo.drawEllipse(QPointF(0,0),raio*fX,raio*fY);
       estojo.rotate(this->amb.getHeadAg(i));
//       estojo.setBrush(QColor(this->amb.getNeig(i)*80,0,255));
       estojo.drawRect(-5,-3,10,6);
       estojo.setBrush(QColor(0,255,255));
       estojo.drawEllipse(QPointF(5,0),3,3);
       estojo.restore();
    }
    estojo.end();
}
