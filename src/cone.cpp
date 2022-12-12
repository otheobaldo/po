#include "../include/forma.h"
#include "../include/ponto3.h"
#include "../include/cone.h"
#include "../include/ponto.h"
#include "../include/Vec3.h"

/**
 * @brief Construtor do sólido geométrico Cone
 * 
 * @param posicao Posição do centro do círculo no R3
 * @param lod Quantidade de pontos, para distorção.
 * @param tAltura Altura do cone
 */
Cone::Cone(Ponto3 posicao,int lod,int tAltura)
:Forma(posicao,1)
{
    LOD = lod;
    Ponto3 temp{0,(double)tAltura,0};
    altura = temp;
    quantidadePontos = LOD + 1;
    calcular_pontos_base();
    calcular_pontos_3D();
    calcular_pontos_2D();
}

void Cone::calcular_pontos_base()
{
    Ponto3* pontosTemp = (Ponto3*)malloc(sizeof(Ponto3) * quantidadePontos);  
    int raio = 1;
    double x,z;
    
    int angulo = 0;
    int posicaoArray = 0; 

    for( ; angulo < 360 ; angulo += 360 / (quantidadePontos -1), posicaoArray++ ){
        x = raio * cos( angulo * M_PI / 180 );
        z = raio * sin( angulo * M_PI / 180);
        Ponto3 ponto{x,posicao.y,z};
        pontosTemp[posicaoArray] = ponto;
    }
    pontosTemp[quantidadePontos-1] = altura;
    pontos_base = pontosTemp;
}

void Cone::desenhar(Window &window)
{
    calcular_pontos_3D();
    calcular_pontos_2D();

    for( int ponto = 1 ; ponto < quantidadePontos-1; ponto++ ){
        window.desenha(projecao[ponto],projecao[ponto - 1]);
        if( ponto == quantidadePontos - 2){
            window.desenha(projecao[ponto],projecao[0]);
        }
        window.desenha(projecao[ponto],projecao[quantidadePontos-1]);
    }
    window.desenha(projecao[0],projecao[quantidadePontos-1]);

}

void Cone::setLOD(int lod){
    if(lod){
        if(LOD<360){
            while(true){
                LOD++;
                if(360%LOD==0){
                    break;
                }
            }
        }
    }
    else{
        if(LOD>3){
            while(true){
                LOD--;
                if(360%LOD==0){
                    break;
                }
            }        
        }
    }

    quantidadePontos = LOD + 1;    
    calcular_pontos_base();

    Ponto3 anguloAntigo = Ponto3(angulo.x,angulo.y,angulo.z);
    angulo.x = 0;
    angulo.y = 0;
    angulo.z = 0;

    girar(anguloAntigo.x,anguloAntigo.y,anguloAntigo.z);

    calcular_pontos_3D();
    calcular_pontos_2D();
    
}

int Cone::getLOD(){
    return LOD;
}

ostream & operator<< (ostream &out, const Cone &p)
{
    return out;
}