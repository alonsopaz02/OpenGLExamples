#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
void ejes(void);
void engranaje02(void);
void vertices(int,int,int);
void nube_puntos(int,int,int);
void polilinea(int,int,int);
void poligono(int,int,int);
void init(void);
void display(void);
void reshape(int,int);
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(100,100);
glutCreateWindow(argv[0]);
init();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMainLoop();
return 0;
}

void engranaje02(void)
{
    float x,y;
    int i,r=14,R=16,N=40;
    float ang,dang=2*M_PI/N;
    glBegin(GL_LINE_LOOP);
    for (i=0;i<N;i++)
        {
        ang=(float)i*dang;

        if(i%2!=0)
        {
            x = r*cos(ang);
            y = r*sin(ang);
            glVertex2f(x,y);
            x = R*cos(ang);
            y = R*sin(ang);
            glVertex2f(x,y);
        }
        else
        {
            x = R*cos(ang);
            y = R*sin(ang);
            glVertex2f(x,y);
            x = r*cos(ang);
            y = r*sin(ang);
            glVertex2f(x,y);
            }


    }
    glEnd();
}

void ejes(void)
{
    glBegin(GL_LINES);
            glVertex2f(-20,0.0);
            glVertex2f(20,0.0);
            glVertex2f(0,-20.0);
            glVertex2f(0,20.0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(20,0.0);
        glVertex2f(20-1,0.5);
        glVertex2f(20-1,-0.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(0.0,10);
        glVertex2f(-0.5,10-1);
        glVertex2f(0.5,10-1);
    glEnd();
}

void vertices(int radio,int h,int k)
{
    float x,y,ang;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/10)
        {
        x = radio * cos(ang)+h;
        y = radio * sin(ang)+k;
        glVertex2f(x,y);
    }
}

void nube_puntos(int radio,int h,int k)
{
    glPointSize(4);
    glBegin(GL_POINTS);
        vertices(radio,h,k);
    glEnd();
}

void polilinea(int radio,int h,int k)
{

    glBegin(GL_LINE_LOOP);
        vertices(radio,h,k);
    glEnd();
}

void poligono(int radio,int h,int k)
{
    glBegin(GL_POLYGON);
        vertices(radio,h,k);
    glEnd();
}

void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
glShadeModel(GL_FLAT);

}

void display(void)
{
GLfloat ang, radio = 8.0f, x, y;
glClear(GL_COLOR_BUFFER_BIT);
glPushMatrix();
glColor3f(0.0,1.0,0.0);
ejes();
glColor3f(1,0.0,0.0);
nube_puntos(4,-15,5);
glColor3f(0,0.0,1.0);
polilinea(4,0,5);
glColor3f(0,0.0,1.0);
glLineWidth(4);
polilinea(4,15,5);
glColor3f(0,1.0,1.0);
poligono(4,-15,-5);
glColor3f(0,0,1);
//engranaje02();

glPopMatrix();      // reecupera el estado del matriz
glFlush();
}
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-20.0,20.0,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
