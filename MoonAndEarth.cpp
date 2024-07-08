#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include <gl/glut.h>

void ejes(int);
GLdouble angulo=0, incremento_angulo=0.1;
GLdouble anguloLuna=0;

GLfloat a=4.5;
GLfloat b=4.4;

GLfloat c = sqrt(a * a - b * b);

GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=10;
GLfloat px1=0,py1=0,pz1=9;
static GLfloat theta[] = {0.0,0.0,0.0};

static GLint axis = 3;



void iniciar(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
}

void drawEllipse(float a, float b) {
    glColor3f(1,1,1);
    glPointSize(2);
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; ++i) {
        GLfloat angle = 2.0f * M_PI * i / 1000;
        GLfloat x = a * cos(angle);
        GLfloat y = b * sin(angle);
        glVertex3f(x, y,0);
    }
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
// la camara se desplaza sobre el plano xz
    gluLookAt(px0,py0,pz0,px1,py1,pz1,0,1,0);
    glColor3f (1.0, 0.0, 0.0);

    ejes(2);
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    glColor3f (0.0, 0.0, 1.0);

    drawEllipse(a,b);


    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(c,0,0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(a*cos(anguloLuna),b*sin(anguloLuna),0);
    glColor3f(0,1,1);
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
void CubeSpin()
{
    theta[axis] += .5;
    if(theta[axis]>360)
        theta[axis] -= 360.0;

    anguloLuna += .05;
    if(anguloLuna>360)
        anguloLuna -= 360.0;
    display();
}


void rotacamara()
{
    px1=px0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}

void rotacamara2()
{
    py1=py0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}


void avanza()
{
    px0=px1;
    pz0=pz1;
    px1=px0+radio*sin(angulo);
    pz1=pz0-radio*cos(angulo);
}
void retro()
{
    px1=px0;
    pz1=pz0;
    px0=px0-radio*sin(angulo);
    pz0=pz0+radio*cos(angulo);
}
void teclado(unsigned char tecla,int x,int y)
{
    switch(tecla)
    {
    case 'i' :
        avanza();
        break;
    case 'm' :
        retro();
        break;
    case 'j' :
        angulo=angulo+incremento_angulo;
        rotacamara();
        break;
    case 'k' :
        angulo=angulo-incremento_angulo;
        rotacamara();
        break;
    case 'p' :
        angulo=angulo-incremento_angulo;
        rotacamara2();
        break;
    case 'a' :
        axis = 0;
        break;
    case 's' :
        axis = 1;
        break;
    case 'd' :
        axis = 2;
        break;
    case 'f' :
        exit(0);
        break;
    }
}
void ejes(int longitud)
{
    //Eje Z Rojo
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3d(0,0,longitud);
    glVertex3d(0,0,0);
    glEnd();

    //Eje Y Verde
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,longitud,0);
    glEnd();

    //Eje X Azul
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(longitud,0,0);
    glEnd();
}


void myReshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h,0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("camara movil");
    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(CubeSpin);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
