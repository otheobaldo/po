#pragma once
#include<SDL2/SDL.h>
#include <iostream>
#include "ponto3.h"
#include "forma.h"
#include "janela.h"
#include "Vec3.h"


using namespace std;

class Cubo : virtual public Forma
{
    public:
    
        Cubo(Ponto3 posicao, double tamanho);
        Cubo(Ponto3 posicao);

        void desenhar(Window &window);
        void calcular_pontos_base();
};

ostream & operator<<(ostream &out, const Cubo &p);