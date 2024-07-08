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

static GLint axis = 2 ;

void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
}

void Mi_Cilindro_Wire(int,float,float,float);

void cilindroHueco(int Npara, float Ncortes, float radio1,float radio2,float altura)
{
    int i=0;
    float x,y=0,z;
    Mi_Cilindro_Wire(Npara,Ncortes,altura,radio1);
    Mi_Cilindro_Wire(Npara,Ncortes,altura,radio2);

    glColor3f(1,1,0);
    glBegin(GL_QUAD_STRIP);
    for (float ang = 0; ang < 2 * M_PI; ang += 2*M_PI/Npara)
    {
        if(i%2==0)
        {
            x = radio2 * cos(ang);
            z = radio2 * sin(ang);
            glVertex3f(x,y,z);
            x = radio1 * cos(ang);
            z = radio1 * sin(ang);
            glVertex3f(x,y,z);
        }
        else
        {
            x = radio2 * cos(ang);
            z = radio2 * sin(ang);
            glVertex3f(x,y,z);
            x = radio1 * cos(ang);
            z = radio1 * sin(ang);
            glVertex3f(x,y,z);
        }
        i++;
    }

    x = radio2 * cos(0);
    z = radio2 * sin(0);
    glVertex3f(x,y,z);

    x = radio1 * cos(0);
    z = radio1 * sin(0);
    glVertex3f(x,y,z);
    glEnd();

     glBegin(GL_QUAD_STRIP);
    for (float ang = 0; ang < 2 * M_PI; ang += 2*M_PI/Npara)
    {
        if(i%2==0)
        {
            x = radio2 * cos(ang);
            z = radio2 * sin(ang);
            glVertex3f(x,altura,z);
            x = radio1 * cos(ang);
            z = radio1 * sin(ang);
            glVertex3f(x,altura,z);
        }
        else
        {
            x = radio2 * cos(ang);
            z = radio2 * sin(ang);
            glVertex3f(x,altura,z);
            x = radio1 * cos(ang);
            z = radio1 * sin(ang);
            glVertex3f(x,altura,z);
        }
        i++;
    }

    x = radio2 * cos(0);
    z = radio2 * sin(0);
    glVertex3f(x,altura,z);

    x = radio1 * cos(0);
    z = radio1 * sin(0);
    glVertex3f(x,altura,z);
    glEnd();
}

void Mi_Cilindro_Wire(int Npara, float Ncortes,float altura,float radio)
{
    int i=0;
    GLfloat posX[Npara],posZ[Npara];
    float x,y=0,z;
    glLineWidth(1);
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for (float ang = 0; ang < 2 * M_PI; ang += 2*M_PI/Npara)
    {
        x = radio * cos(ang);
        z = radio * sin(ang);
        posX[i] = x;
        posZ[i] = z;
        i++;
        glVertex3f(x,y,z);
    }
    glEnd();


    for(int i=0; i<Ncortes+1; i++)
    {
        glBegin(GL_LINE_LOOP);
        for(int j=0; j<Npara; j++)
        {
            x=posX[j];
            z=posZ[j];
            y=altura*i/Ncortes;
            glVertex3f(x,y,z);
        }
        glEnd();
    }



    glBegin(GL_LINES);
    for(int i=0; i<Npara; i++)
    {
        x=posX[i];
        z=posZ[i];
        glVertex3f(x,0,z);
        glVertex3f(x,altura,z);
    }
    glEnd();



    glBegin(GL_QUAD_STRIP);
    for(int i=0; i<Npara; i++)
    {
        if(i==Npara-1)
        {
            glVertex3f(posX[i],0,posZ[i]);
            glVertex3f(posX[0],0,posZ[0]);
            glVertex3f(posX[i],altura,posZ[i]);
            glVertex3f(posX[0],altura,posZ[0]);
        }
        else
        {
            glVertex3f(posX[i],0,posZ[i]);
            glVertex3f(posX[i+1],0,posZ[i+1]);
            glVertex3f(posX[i],altura,posZ[i]);
            glVertex3f(posX[i+1],altura,posZ[i+1]);
        }

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

    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);
    ejes(2);

    glColor3f (0.0,0.0, 0.0);
    cilindroHueco(16,15,1,0.5,2);

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
