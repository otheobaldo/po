#include "../include/forma.h"
#include "../include/ponto3.h"
#include "../include/cilindro.h"
#include "../include/ponto.h"
#include "../include/Vec3.h"

/**
 * @brief Construtor do sólido Cilindro
 * 
 * @param posicao Ponto do centro da base
 * @param lod Nivel de detalhe
 * @param Altura Altura do cilindro
 * 
 * @author Fernanda Martins
 */

Cilindro::Cilindro(Ponto3 posicao, int lod, int Altura)
:Forma(posicao,1)
{
    LOD = lod;
    Ponto3 temp{0,(double)Altura,0};
    altura = temp;
    quantidadePontos = LOD;
    calcular_pontos_base();
    calcular_pontos_3D();
    calcular_pontos_2D();
}

/**
 * @brief Calcula os pontos do cilindro
 * 
 * @author Fernanda Martins
 */

void Cilindro::calcular_pontos_base()
{
    if (quantidadePontos%2 != 0){
        quantidadePontos++;
    }
    Ponto3* pontosTemp = (Ponto3*)malloc(sizeof(Ponto3) * quantidadePontos); 
    int raio = 1;
    double x,z, tmp;
    
    int angulo = 0;
    int posicaoArray = 0; 

    for( ; angulo < 360 ; angulo += 360 / (quantidadePontos/2), posicaoArray+=2){
        x = raio * cos( angulo * M_PI / 180 );
        z = raio * sin( angulo * M_PI / 180);
        tmp = posicao.y + altura.y;
        Ponto3 ponto{x,posicao.y,z};
        Ponto3 ponto1{x,tmp,z};
        pontosTemp[posicaoArray] = ponto;
        pontosTemp[posicaoArray+1] = ponto1;
    }
    //Todos os pontos são armazenados em ponto_base
    pontos_base = pontosTemp;
}

/**
 * @brief Desenha as ligações entre os pontos
 * 
 * @param window Janela 
 * 
 * @author Fernanda Martins
 */

void Cilindro::desenhar(Window &window)
{
    calcular_pontos_3D();
    calcular_pontos_2D();

    for( int ponto = 0 ; ponto < quantidadePontos-1; ponto++ ){
        
        if ( ponto%2 == 0){
            window.desenha(projecao[ponto],projecao[ponto+1]);
            if (ponto == quantidadePontos-2){
                window.desenha(projecao[ponto],projecao[0]);
            }
            else
                window.desenha(projecao[ponto],projecao[ponto + 2]);
        }
        else{            
            if( ponto == quantidadePontos)
                window.desenha(projecao[ponto],projecao[1]);
            else{
                window.desenha(projecao[ponto],projecao[ponto + 2]);
            }        
        } 
    }
    window.desenha(projecao[quantidadePontos-1],projecao[1]);
}

/**
 * @brief Muda tamanho de uma das bases 
 * 
 * @param lado Qual base sofre aumento, se par é a base superior, caso contrario é a base inferior
 * @param tamanho Aumenta ou diminui de acordo com proporção
 * 
 * @author Fernanda Martins
 */

void Cilindro::mudar_base(size_t lado, double tamanho){
    double x,z, tmp;
    
    int angulo = 0;
    int posicaoArray = 0;     
    
        for( ; angulo < 360 ; angulo += 360 / (quantidadePontos/2), posicaoArray+=2){
            x = tamanho * cos( angulo * M_PI / 180 );
            z = tamanho * sin( angulo * M_PI / 180);
            
            if (lado%2 == 1){
                Ponto3 ponto{x,posicao.y,z};
                pontos_base[posicaoArray] = ponto;
            }
            else{
                tmp = posicao.y + altura.y;
                Ponto3 ponto{x,tmp,z};
                pontos_base[posicaoArray+1] = ponto;
            }
        }
}

/**
 * @brief Definir o nível de detalhe
 * 
 * @param lod nível de detalhe
 * 
 * @author José Mateus
 */

void Cilindro::setLOD(int lod){
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

    quantidadePontos = LOD;    
    calcular_pontos_base();

    Ponto3 anguloAntigo = Ponto3(angulo.x,angulo.y,angulo.z);
    angulo.x = 0;
    angulo.y = 0;
    angulo.z = 0;

    girar(anguloAntigo.x,anguloAntigo.y,anguloAntigo.z);

    calcular_pontos_3D();
    calcular_pontos_2D();
    
}

/**
 * @brief Retornar o nível de detalhe
 * 
 * @param lod nível de detalhe
 * 
 * @author José Mateus
 */

int Cilindro::getLOD()
{
    return LOD;
}

ostream & operator<< (ostream &out, const Cilindro &p)
{
    return out;
}