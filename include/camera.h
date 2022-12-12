#include "ponto3.h"
#pragma once
class Camera
{
protected:
    Camera(Ponto3 posicao = Ponto3(0,0,0), int distf = 500);
public:
    Ponto3 posicao;
    double angulox;
    double anguloy;
    int distf;
    static Camera* camera;

    static Camera* criar();    
    void mover(double x = 0.0,double y = 0.0,double z = 0.0);
    void rodarx(double angulo, Ponto3 base);
    void rodary(double angulo, Ponto3 base);
    void rodarz(double angulo, Ponto3 base);

    ~Camera();
};

