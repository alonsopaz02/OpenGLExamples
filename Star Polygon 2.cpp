#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <cmath>


bool sonIguales(float a, float b, float tolerancia = 1e-5) {
    // Calcula el valor absoluto de la diferencia entre a y b
    float diferencia = std::fabs(a - b);

    // Compara la diferencia con la tolerancia
    if (diferencia <= tolerancia) {
        return true;
    } else {
        return false;
    }
}

void vertices(float N, float k)
{
    float r=8.0f;
    float x,y,ang;
    float x0,y0;
    int con=0;
    for (ang = 0.0f; ang<k*2*M_PI; ang += k*2*M_PI/N)
    {
        x = r*cos(ang);
        y = r*sin(ang);
        glVertex2f(x,y);
    }
}


void verticesPoli(float N){
    glBegin(GL_LINE_LOOP);
float r = 8.0f;
    float x,y,ang;
     for (ang = 0.0f; ang<2*M_PI; ang += 2*M_PI/N)
    {
        x = r*cos(ang);
        y = r*sin(ang);
        glVertex2f(x,y);
    }
    glEnd();
}

void polilinea(float N, float k)
{
    glBegin(GL_LINE_LOOP);
    vertices(N,k);
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

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    ejes();
    glColor3f(0,0.0,1.0);
    polilinea(7,4);
    glColor3f(0,1.0,0);
    verticesPoli(7);
    glPopMatrix();      // reecupera el estado del matriz
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-10.0,10,-10.0,10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,250);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}