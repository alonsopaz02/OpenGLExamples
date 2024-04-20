#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <D:\Descargas Chrome\GLUT\GLUT\INCLUDE\GL\glut.h>

void verticesCircu(float r, float h, float k)
{
    float x, y, ang;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2 * M_PI / 24)
    {
        x = r * cos(ang) + h;
        y = r * sin(ang) + k;
        glVertex2f(x, y);
    }
}

void verticesCircu2(float r, float h, float k)
{
    float x, y, ang;
    for (ang = M_PI / 2; ang < 3 * M_PI / 2; ang += 2 * M_PI / 24)
    {
        x = r * cos(ang) + h;
        y = r * sin(ang) + k;
        glVertex2f(x, y);
    }
}

void verticesCircu3(float r, float h, float k)
{
    float x, y, ang;
    for (ang = M_PI / 2; ang > -2 * M_PI; ang -= 2 * M_PI / 24)
    {
        x = r * cos(ang) + h;
        y = r * sin(ang) + k;
        glVertex2f(x, y);
    }
}

void polilinea(float r, float h, float k)
{
    glBegin(GL_POLYGON);
    verticesCircu(r, h, k);
    glEnd();
}

void polilinea2(float r, float h, float k)
{
    glBegin(GL_POLYGON);
    verticesCircu2(r, h, k);
    glEnd();
}

void polilinea3(float r, float h, float k)
{
    glBegin(GL_POLYGON);
    verticesCircu3(r, h, k);
    glEnd();

}

void circunferencia(float r, float h, float k)
{
    glBegin(GL_LINE_LOOP);
    verticesCircu(r, h, k);
    glEnd();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  //parametros: rojo, amarillo, azul, el cuarto es el parametro alpha
    glShadeModel(GL_FLAT);

}

void negro()
{
    glColor3f(0.0, 0.0, 0.0);
}

void blanco()
{
    glColor3f(1.0, 1.0, 1.0);
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    negro();
    circunferencia(6, 0, 0);

    negro();
    polilinea2(6, 0, 0);

    blanco();
    polilinea2(3, 0, 3);

    negro();
    polilinea3(3, 0, -3);

    blanco();
    polilinea(1, 0, -3);

    negro();
    polilinea(1, 0, 3);

    glPopMatrix();      // reecupera el estado del matriz
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-8.0, 8.0, -8.0, 8, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
