#include "../include/forma.h"
#include "../include/ponto3.h"
#include "../include/esfera.h"
#include "../include/ponto.h"
#include "../include/Vec3.h"

/**
 * @brief Construtor do sólido geométrico Esfera
 * 
 * @param posicao posição do centro no R3
 * @param tamanho Raio da esfera
 * @param lod Quantidade de pontos, para distorção
 */
Esfera::Esfera(Ponto3 posicao, double tamanho, int lod)
:Forma(posicao,tamanho),LOD{lod}
{
    iluminacao = Vec3(1,1,0);
    faixas = LOD / 2 + 1;
    quantidadePontos = LOD * faixas;
    calcular_pontos_base();
    calcular_pontos_3D();
    calcular_pontos_2D();
}

Esfera::Esfera(Ponto3 posicao,int lod)
:Forma(posicao,1),LOD{lod}
{
    iluminacao = Vec3(1,1,0);
    faixas = LOD / 2 + 1;
    quantidadePontos = LOD * faixas;
    calcular_pontos_base();
    calcular_pontos_3D();
    calcular_pontos_2D();
}

void Esfera::calcular_pontos_base()
{
    Ponto3* pontosTemp = (Ponto3*)malloc(sizeof(Ponto3) * quantidadePontos);
    Ponto3* paraCalculo = (Ponto3*)malloc(sizeof(Ponto3) * LOD);

    int raio = tamanho;
    int p = 0;
    double x,y,z;
    int ps = 0;
    int rotacao = 360 / LOD;
    double seno = sin( rotacao * M_PI / 180 );
    double cosseno = cos( rotacao * M_PI / 180 );

    for( int i = 0 ; i < 360 ; i += 360 / LOD,p++){
        x = raio * cos( i * M_PI / 180 );
        y = raio * sin( i * M_PI / 180 );
        Ponto3 ponto{x,y,0};
        paraCalculo[p] = ponto;
    }

    for( int a = 0; a < faixas; a++){
        for( int j = 0 ; j < p ; j++, ps++ ){
            x = paraCalculo[j].x;
            z = paraCalculo[j].z;
            paraCalculo[j].x = x * cosseno - z * seno;
            paraCalculo[j].z = z * cosseno + x * seno;
            pontosTemp[ps] = Ponto3(paraCalculo[j].x,paraCalculo[j].y,paraCalculo[j].z);
        }
    }

    pontos_base = pontosTemp;    
}

void Esfera::desenhar(Window &window)
{
    calcular_pontos_3D();
    calcular_pontos_2D();
    
    int index;
    int type = 0;
    int R = 255;
    int G = 255;
    int B = 255;
    double angulo;
    double a[3] = {posicao.x,posicao.y,posicao.z};
    double b[3];
    double c[3];
    double origem[3] = {0,0,0};
    Vec3 camToObj{origem,a};

    for(int j = 0; j < quantidadePontos; j++)
    {
        if( ( ( j + 1 ) % LOD ) == 0 ) {
            index = j - LOD + 1;
        }
        else{
            index = j + 1;
        }

        switch(type){
            case 1:
                window.desenha( projecao[j],projecao[index]);
                if( j > LOD - 1 ){
                    window.desenha( projecao[j], projecao[ j - LOD ]);
                }  
                break;

            case 0:
                
                b[0] = pontos[j].x;
                b[1] = pontos[j].y;
                b[2] = pontos[j].z;
                c[0] = pontos[index].x;
                c[1] = pontos[index].y;
                c[2] = pontos[index].z;

                Vec3 objToponto1(a,b);
                Vec3 objToponto2(a,c);

                if(camToObj.angulo_entre_vetores(objToponto1) > 90 && camToObj.angulo_entre_vetores(objToponto2) > 90){
                    if( j > LOD - 1 ){
                        if(comSombra){
                            angulo = ( objToponto1.angulo_entre_vetores(iluminacao) + objToponto2.angulo_entre_vetores(iluminacao) ) / 2 ;
                            R = corR - (( 255 / 180 ) * angulo);
                            G = corG - (( 255 / 180 ) * angulo);
                            B = corB - (( 255 / 180 ) * angulo);
                        }
                        else{
                            R = corR;
                            G = corG;
                            B = corB;
                        }
                        window.desenhar_poligono(projecao[j],projecao[j - LOD],projecao[j - LOD + 1],R,G,B);
                        window.desenhar_poligono(projecao[j],projecao[j - 1],projecao[j - LOD],R,G,B);
                    }
                }
                break;       
        }
    }
}

void Esfera::setLOD(int lod){
    if(lod){
        if(LOD<=360){
            while(true){
                LOD++;
                if(360%LOD==0){
                    break;
                }
            }
        }
    }
    else{
        if(LOD>=6){
            while(true){
                LOD--;
                if(360%LOD==0){
                    break;
                }
            }        
        }
    }

    faixas = LOD / 2 + 1;
    quantidadePontos = LOD * faixas;    
    calcular_pontos_base();

    Ponto3 anguloAntigo = Ponto3(angulo.x,angulo.y,angulo.z);
    angulo.x = 0;
    angulo.y = 0;
    angulo.z = 0;

    girar(anguloAntigo.x,anguloAntigo.y,anguloAntigo.z);

    calcular_pontos_3D();
    calcular_pontos_2D();
    
}

int Esfera::getLOD(){
    return LOD;
}



ostream & operator<< (ostream &out, const Esfera &p)
{
    return out;
}