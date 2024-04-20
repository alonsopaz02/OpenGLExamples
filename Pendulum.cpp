#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

static GLfloat theta[] = {20.0,240.0,0.0,0.0};
static GLfloat increment=1;
// eje es el ángulo a rotar
static GLint eje = 3;
// construya su poligono base
static GLfloat tras[] = {0,0,0};
static GLfloat angulo = -60;

void ejes(void)
{
    //X rojo
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(-2.0,0,0);
    glVertex3f(2,0,0);
    glEnd();

    //Y azul
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,-2,0);
    glVertex3f(0,2,0);
    glEnd();

    //Z verde
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,0,-2);
    glVertex3f(0,0,2);
    glEnd();
}
void cuerda(void)
{
    glColor3f(1,1,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(tras[0], tras[1], 0);
    glVertex3f(0, 1, 0);
    glEnd();
}

// dibujamos nuestra escena
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // composicion de rotaciones
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    //cubo();
    ejes();
    cuerda();
    glColor3f(0,0,1);
    glLineWidth(3);
    glTranslatef(tras[0],tras[1],tras[2]);
    glutWireSphere(0.25, 10, 10);
    glColor3f(1,1,1);
    glutSolidSphere(0.25, 10, 10);
    //cubosconcentricos();
    glFlush();
    // intercambiamos los buffers, el que se muestra y el que esta oculto
    glutSwapBuffers();
}
// esta función controla el angulo de rotación según el eje de giro
void girar_objeto_geometrico ()
{
    if(eje==3){
        display();
    }
    theta[eje] += 0.01;
    if(theta[eje]>360)
        theta[eje]-=360.0;


    cout<<(angulo)<<endl;
//240 y 300
    angulo += increment;
    if (angulo < -60) {
            increment = 0.1; // Avanzar a 300
        } else if (angulo == 60) {
            increment = -0.1; // Retroceder a 240
        }

    tras[0] = 1*sin(angulo*2*M_PI/360);
    tras[1] = -1*cos(angulo*2*M_PI/360);
    tras[2] = 0;
    cout<<(tras[0])<<endl;
    cout<<(tras[1])<<endl;

    display();
}
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case 'a' :
        eje = 0;
        break;
    case 's' :
        eje = 1;
        break;
    case 'd' :
        eje = 2;
        break;
    case 'f' :
        eje = 3 ;
        break;
    }
}
// control de ventana (recuerde el volumen de visualización)
// modifique dicho volumen según su conveniencia
void myReshape(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <=h)
        glOrtho(-5.0,5.0,-5.0*(GLfloat)h/(GLfloat)w,
                5.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-5.0*(GLfloat)w/(GLfloat)h,
                5.0*(GLfloat)w/(GLfloat)h, -5.0,5.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("mi objeto bajo rotaciones");
    glutReshapeFunc(myReshape);
    // invocamos a display() para dibujar nuestra escena
    glutDisplayFunc(display);
    // esta funcion llama a girar_objeto_geométrico() mientras no haya evento
    // alguno ocasionado por el usuario
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    /*glutMouseFunc(mouse);*/
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}