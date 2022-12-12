#include "../include/camera.h"

/**
 * @brief Construtor da Camera, posição do Pinhole
 * @authors Gustavo Mittelmann, Henrique Heiderscheidt
 * @param posicao posição do pinhole no r3
 * @param distf distancia focal
 */
Camera::Camera(Ponto3 posicao, int distf)
:posicao{posicao},distf{distf}
{
    angulox = 0;
    anguloy = 0;
}

/**
 * @brief Rodar a camera no eixo x baseado em um ponto de foco no R3.
 * @author Henrique Heiderscheidt
 * @param angulo angulo de rotacao
 * @param base Ponto de foco
 * 
 * @todo Talvez mudar a forma de visualizar a camera.
 */
void Camera::rodarx(double angulo, Ponto3 base){
    posicao.y = posicao.y*cos(angulo)+posicao.z*-sin(angulo);
    posicao.z = posicao.y*sin(angulo) + posicao.z*cos(angulo);
}

/**
 * @brief Rodar a camera no eixo y baseado em um ponto de foco no R3.
 * @author Henrique Heiderscheidt
 * @param angulo angulo de rotacao
 * @param base Ponto de foco
 * 
 * @todo Talvez mudar a forma de visualizar a camera.
 */
void Camera::rodary(double angulo,Ponto3 base){
    posicao.x = ((posicao.x - base.x)*cos(angulo) + (posicao.z-base.z)*-sin(angulo)) + base.x;
    posicao.z = ((posicao.x - base.z)*sin(angulo) + (posicao.z-base.z)*cos(angulo)) + base.z;
}

/**
 * @brief Rodar a camera no eixo z baseado em um ponto de foco no R3.
 * @author Henrique Heiderscheidt
 * @param angulo Angulo de rotacao
 * @param base Ponto de foco
 * 
 * @todo Talvez mudar a forma de visualizar a camera.
 */
void Camera::rodarz(double angulo, Ponto3 base){
    posicao.x = ((posicao.x - base.x)*cos(angulo)  + (posicao.y - base.y)*-sin(angulo)) + base.x;
    posicao.y = ((posicao.x - base.x)*sin(angulo)  + (posicao.y - base.y)*cos(angulo)) + base.y;
}

/**
 * @brief Mover a camera no espaco, no momento muda todos os pontos baseados na posicao da camera
 * @authors Gustavo Mittelmann, Henrique Heiderscheidt
 * @param posicao posição do pinhole no r3
 * @param distf distancia focal
 */
void Camera::mover(double x,double y,double z){
    posicao.x += x;
    posicao.y += y;
    posicao.z += z;
}

//Definicao do ponteiro para a classe Singleton.
Camera *Camera::camera = nullptr;


/**
 * @brief Singleton da classe camera, só permite uma instacia da classe.
 * @authors Gustavo Mittelmann, Henrique Heiderscheidt
 * @return Camera* 
 */
Camera *Camera::criar(){
    if (camera == nullptr){
        camera = new Camera();
    };
    return camera;
    }


Camera::~Camera()
{
}