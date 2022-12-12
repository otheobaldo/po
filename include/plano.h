#pragma once
#include<SDL2/SDL.h>
#include <iostream>
#include "ponto3.h"
#include "forma.h"
#include "janela.h"
#include "Vec3.h"

using namespace std;

class Plano : virtual public Forma
{
    private:
        int LOD;
        int largura, comprimento;
        
    public:
        
        Plano(Ponto3 posicao, int largura);
        
        void desenhar(Window &window);
        void calcular_pontos_base();
        void revolucao();

        void setLOD(int lod);
        int getLOD();
};

ostream & operator<<(ostream &out, const Plano &p);