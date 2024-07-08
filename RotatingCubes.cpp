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
GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=5;
GLfloat px1=0,py1=0,pz1=4;
static GLfloat theta[] = {0.0,0.0,0.0};

GLfloat centrosCubosX[] = {0.0,0.0,0.0,0,0,0};
GLfloat centrosCubosY[] = {0.0,0.0,0.0,0,0,0};
static GLint axis = 2 ;
void drawHexagonalBox();
void posicionesCubos();


void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
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
    //glutWireSphere(1.0, 8, 3);
    drawHexagonalBox();
    posicionesCubos();


    glPushMatrix();
    glTranslatef(centrosCubosX[0],centrosCubosY[0],0);
    glRotatef(30,0,0,1);
    glutWireCube(1);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(centrosCubosX[1],centrosCubosY[1],0);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(centrosCubosX[2],centrosCubosY[2],0);
    glRotatef(150,0,0,1);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(centrosCubosX[3],centrosCubosY[3],0);
    glRotatef(210,0,0,1);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(centrosCubosX[4],centrosCubosY[4],0);
    glRotatef(270,0,0,1);
    glutWireCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(centrosCubosX[5],centrosCubosY[5],0);
    glRotatef(330,0,0,1);
    glutWireCube(1);
    glPopMatrix();

    //glutWireDodecahedron();
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
void CubeSpin()
{
    theta[axis] += .5;
    if(theta[axis]>360)
        theta[axis] -= 360.0;
    display();
}

void posicionesCubos(){
    glPointSize(5);
    glBegin(GL_POINTS);
    float radioc = 0.5*sqrt(3)+0.5;
    float x,y,z,ang;
    int i=0;
    for (ang = 2*M_PI/12; ang < 2 * M_PI; ang += 2*M_PI/6)
    {
        x = radioc * cos(ang);
        y = radioc * sin(ang);
        z=0;
        centrosCubosX[i]=x;
        centrosCubosY[i]=y;
        glVertex3f(x,y,z);
        i++;
    }
    glEnd();
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
    glBegin(GL_LINES);
    glVertex3d(0,0,longitud);
    glVertex3d(0,0,0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,longitud,0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(longitud,0,0);
    glEnd();
}

void drawHexagonalBox() {
     glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 6; i++) {
        float angle = 2.0 * M_PI * i / 6;
        float x = cos(angle);
        float y = sin(angle);
        float z = 0.5;
        glVertex3f(x, y,z);
    }

    glEnd();

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 6; i++) {
        float angle = 2.0 * M_PI * i / 6;
        float x = cos(angle);
        float y = sin(angle);
        float z = -0.5;
        glVertex3f(x, y,z);
    }

    glEnd();

    glBegin(GL_LINES);

    for (int i = 0; i < 6; i++) {
        float angle = 2.0 * M_PI * i / 6;
        float x = cos(angle);
        float y = sin(angle);
        float z = 0.5;
        glVertex3f(x, y,z);
        glVertex3f(x, y,-z);
    }

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
