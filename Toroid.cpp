#include <stdlib.h>
#include<conio.h>
#include <gl/glut.h>
#include <math.h>

void torus (int, int,float,float);
float angulo=0,dangulo=0.02;
void createTorusList();
void createTorusList2();

static GLfloat theta[] = {0.0,0.0,0.0};

static GLint eje = 2;

GLuint torusList;
void createTorusList()
{
    torusList = glGenLists(1);
    glNewList(torusList, GL_COMPILE);
    torus(20, 20,5,1.5);
    glEndList();
}

GLuint torusList2;
void createTorusList2()
{
    torusList2 = glGenLists(1);
    glNewList(torusList2, GL_COMPILE);
    torus(20, 20,2.5,0.75);
    glEndList();
}

void circulo1(float r,float h, float k)
{
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    float x,y,ang;
    for (ang = M_PI/2; ang<3*M_PI/2; ang += 2*M_PI/24)
    {
        x = r*cos(ang)+h;
        y = r*sin(ang)+k;
        glVertex3f(x,y,0);
    }
    glEnd();
    glLineWidth(1);
}

void circulo2(float r,float h, float k)
{
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    float x,y,ang;
    for (ang = -M_PI/2; ang<M_PI/2; ang += 2*M_PI/24)
    {
        x = r*cos(ang)+h;
        y = r*sin(ang)+k;
        glVertex3f(x,y,0);
    }
    glEnd();
    glLineWidth(1);
}

void lineas(float h1,float h2, float k1, float k2, float r1, float r2){
    glLineWidth(4);
    float x,y,ang;
    glBegin(GL_LINES);
    x = r2*cos(-M_PI/2)+h2;
    y = r2*sin(-M_PI/2)+k2;
    glVertex3f(x,y,0);

    x = r1*cos(3*M_PI/2)+h1;
    y = r1*sin(3*M_PI/2)+k1;
    glVertex3f(x,y,0);

    x = r1*cos(M_PI/2)+h1;
    y = r1*sin(M_PI/2)+k1;
    glVertex3f(x,y,0);

    x = r2*cos(M_PI/2)+h2;
    y = r2*sin(M_PI/2)+k2;
    glVertex3f(x,y,0);

     x = r1*cos(M_PI/2)+h1;
    y = r1*sin(M_PI/2)+k1;
    glVertex3f(x,y,0);
    glEnd();
    glLineWidth(1);
}


void torus(int numc, int numt,float radioMenor,float radioMayor)
{
    int i, j, k;
    double s, t, x, y, z, twopi;
    twopi = 2 * M_PI;
    for (i = 0; i < numc; i++)
    {
        glBegin(GL_LINE_STRIP);
        for (j = 0; j <= numt; j++)
        {
            for (k = 1; k >= 0; k--)
            {
                s = (i + k) % numc + 0.5;
                t = j % numt;
                //Radio menor
                x = (radioMenor+radioMayor*cos(s*twopi/numc))*cos(t*twopi/numt);
                //Radio mayor
                y = (radioMenor+radioMayor*cos(s*twopi/numc))*sin(t*twopi/numt);
                //Grosor
                z = 1.5 * sin(s * twopi / numc);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_FLAT);
    createTorusList();
    createTorusList2();
}

void punto(){
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex3f(-10,-5,0);
    glVertex3f(-10,7.5,0);
    glVertex3f(10,-5,0);
    glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    circulo1(6.5,-10,-5);
    glColor3f(1,0,0);
    circulo2(3.25,10,-5);
    lineas(-10,10,-5,-5,6.5,3.25);
    punto();

    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(-10,-5,0);
    glRotatef(theta[2],0.0,0.0,1.0);
    glCallList(torusList);
    glPopMatrix();



    glPushMatrix();
    glColor3f(1,1.5,0);
    glTranslatef(-10,7.5,0);
    glRotatef(-theta[2],0.0,0.0,1.0);
    glCallList(torusList);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,0,1.5);
    glTranslatef(10,-5,0);
    glRotatef(theta[2],0.0,0.0,1.0);
    glCallList(torusList2);
    glPopMatrix();





    glFlush();
    glutSwapBuffers();
}


void girar_objeto_geometrico ()
{
    theta[eje] += 0.01;
    if(theta[eje]>360)
        theta[eje]-=360.0;

    angulo+=dangulo;
    if(angulo <-30 || angulo >30)
        dangulo=-dangulo;

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
        exit(0) ;
        break;
    }
}


void myReshape(int w, int h)
{
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-20.0,20,-20.0,20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("mi objeto bajo rotaciones");
    init();
    glutReshapeFunc(myReshape);

    glutDisplayFunc(display);

    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    /*glutMouseFunc(mouse);*/
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}