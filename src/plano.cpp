#include "../include/forma.h"
#include "../include/ponto3.h"
#include "../include/plano.h"
#include "../include/ponto.h"
#include "../include/Vec3.h"

/**
 * @brief Construtor do Plano Quadrado
 * 
 * @param posicao Ponto do centro do plano
 * @param largura Largura do plano
 * 
 * @author Fernanda Martins
 */

Plano::Plano(Ponto3 posicao, int largura)
:Forma(posicao,1), largura{largura}
{
    quantidadePontos = largura*largura;

    calcular_pontos_base();
    calcular_pontos_3D();
    calcular_pontos_2D();
}

/**
 * @brief Calcula os pontos do plano
 * 
 * @author Fernanda Martins
 */

void Plano::calcular_pontos_base()
{
    int a = 0;
    Ponto3* pontosTemp = (Ponto3*)malloc(sizeof(Ponto3) * quantidadePontos); 
    for (int i = 0; i < largura; i++){
        for (int j= 0; j < largura; j++){
            Ponto3 ponto{i,0,j};
            pontosTemp[a] = ponto;
            a++;
        }
    }
    //Todos os pontos são armazenados em ponto_base
    pontos_base = pontosTemp;
}

/**
 * @brief Desenha as ligações entre os pontos do plano que formam angulos de 90 graus
 * 
 * @param window Janela 
 * 
 * @author Fernanda Martins
 */

void Plano::desenhar(Window &window)
{
    calcular_pontos_3D();
    calcular_pontos_2D();
    int ponto = 0;
    int i = 1;

    for( ; ponto < quantidadePontos-1; ponto++ ){
        if (i != largura){
            window.desenha(projecao[ponto],projecao[ponto+1]);
            i++;
        }
        else {
            window.desenha(projecao[ponto],projecao[ponto+largura]);
            i = 1;
        }            
    }
    int x = quantidadePontos-largura;
    ponto = 0;
    for( ; ponto < largura; ponto++ ){
        window.desenha(projecao[ponto],projecao[x]);
        x = x+1;
    }
}

ostream & operator<< (ostream &out, const Plano &p)
{
    return out;
}