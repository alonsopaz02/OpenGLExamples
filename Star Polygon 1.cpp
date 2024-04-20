#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>


void init(void);
void display(void);
void polilinea(int,int,int);
void reshape(int,int);
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

void vertices(int radio1,int radio2,int h,int k)
{
    float x,y,ang;
    int n=0;
    for (ang = 0.0f; ang < 2 * M_PI; ang += 2*M_PI/20)
    {
        if(n%2==1)
        {
            x = radio2 * cos(ang)+h;
            y = radio2 * sin(ang)+k;
            glVertex2f(x,y);
        }
        else
        {
            x = radio1 * cos(ang)+h;
            y = radio1 * sin(ang)+k;
            glVertex2f(x,y);
        }
        n++;
    }
}

void polilinea(int radio1,int radio2,int h,int k)
{
    glBegin(GL_LINE_LOOP);
    vertices(8,6,0,0);
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
    glColor3f(0,0.0,1.0);
    polilinea(4,8,0,0);
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