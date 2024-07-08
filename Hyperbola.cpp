#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

void verticesHiper(){
    int x,y;
    glBegin(GL_LINES);
    for(int i=1;i<16;i++){
        x=i;
        y=16-i;
        glVertex2f(x,0);
        glVertex2f(0,y);

        glVertex2f(x,0);
        glVertex2f(0,(-1)*y);

        glVertex2f((-1)*x,0);
        glVertex2f(0,y);

        glVertex2f((-1)*x,0);
        glVertex2f(0,(-1)*y);
    }
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
    glColor3f(0,0.0,0);
    glLineWidth(2);
    verticesHiper();
    glPopMatrix();      // reecupera el estado del matriz
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0,15.0,-15.0,15,-15.0,15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

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

