#pragma once
#include<SDL2/SDL.h>
#include <iostream>
#include "ponto3.h"
#include "forma.h"
#include "janela.h"
#include "Vec3.h"

using namespace std;

class Esfera : virtual public Forma
{
    private:
        int LOD;
        int faixas;
        
    public:
        
        Esfera(Ponto3 posicao, double tamanho, int lod);
        Esfera(Ponto3 posicao, int lod);

        void desenhar(Window &window);
        void calcular_pontos_base();

        void setLOD(int lod);
        int getLOD();
};

ostream & operator<<(ostream &out, const Esfera &p);