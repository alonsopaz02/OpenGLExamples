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

GLfloat incremento=0.1;

GLdouble const radio=0.5;
GLfloat px0=0,py0=0,pz0=20;
GLfloat px1=0,py1=0,pz1=18;
static GLfloat theta[] = {0.0,0.0,0.0};
int pos=0;

GLfloat yCilindro=-2,yJala;


static GLint axis = 3;



void iniciar(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);
}

void disco(float radio)
{
    float x,y;
    float xs[50],ys[50];
    int i=0;
    glColor3f(0.5,0.5,0.5);
    glLineWidth(5);
    glBegin(GL_POLYGON);
    for (float ang = 0; ang < 2 * M_PI; ang += 2*M_PI/50)
    {
        x = radio * cos(ang);
        xs[i]=x;
        y = radio * sin(ang);
        ys[i]=y;
        glVertex3f(x,y,0.5);
        i++;
    }
    glEnd();

    glBegin(GL_POLYGON);
    for(int j=0;j<50;j++){
        x = xs[j];
        y = ys[j];
        glVertex3f(x,y,-0.5);
    }
    glEnd();


    glColor3f(0.5, 0.25, 0.0);
    glBegin(GL_QUAD_STRIP);
    for(int j=0;j<50;j++){
        glVertex3f(xs[j]/2,ys[j]/2,.5);
        glVertex3f(xs[j+1]/2,ys[j+1]/2,.5);
        glVertex3f(xs[j]/2,ys[j]/2,-.5);
        glVertex3f(xs[j+1]/2,ys[j+1]/2,-.5);
    }
    glEnd();
}

void faja(float radio){

    float xc,yc;
    glLineWidth(5);
    glTranslatef(0,8,0);
    glBegin(GL_LINE_STRIP);
    for (float ang = 0; ang < M_PI; ang += 2*M_PI/50)
    {
        xc = radio * cos(ang);
        yc = radio * sin(ang);
        glVertex3f(xc,yc,0);
    }
    glEnd();

}
void cilindro(float radio, float altura){
    float x,y,z;
    int i=0;

    float xs[50],ys[50];

    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluCylinder(quadric, radio, radio, altura, 32, 32);
    glBegin(GL_POLYGON);
    for (float ang = 0; ang < 2 * M_PI; ang += 2*M_PI/50)
    {
        x = radio * cos(ang);
        xs[i]=x;
        y = radio * sin(ang);
        ys[i]=y;
        i++;
        glVertex3f(x,y,altura);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (float ang = 0; ang < 2 * M_PI; ang += 2*M_PI/50)
    {
        x = radio * cos(ang);
        y = radio * sin(ang);
        glVertex3f(x,y,0);
    }
    glEnd();

    glColor3f(0,0,0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<50;i++){
        x=xs[i];
        y=ys[i];
        glVertex3f(x,y,0);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for(int i=0;i<50;i++){
        x=xs[i];
        y=ys[i];
        glVertex3f(x,y,altura);
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


    glTranslatef(0,-2,0);
    glRotatef(theta[0],1.0,0.0,0.0);
    glRotatef(theta[1],0.0,1.0,0.0);
    glRotatef(theta[2],0.0,0.0,1.0);

    ejes(2);

    glColor3f(1,1,0);



    glPushMatrix();
    glTranslatef(0,8,0);
    disco(2);
    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(-1,yCilindro,0);
    glRotatef(270,1,0,0);
    cilindro(1,2);
    glPopMatrix();


    glPushMatrix();
    faja(1);
    glPopMatrix();


    glPushMatrix();
    glLineWidth(3);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3f(-1,8,0);
    glVertex3f(-1,yCilindro,0);

    glVertex3f(1,yJala,0);
    glVertex3f(1,8,0);
    glEnd();

    glPushMatrix();
    glColor3f(1,0,1);
    glTranslatef(1,yJala,0);
    glutSolidSphere(0.5,10,10);
    glPopMatrix();

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

    if(yCilindro>4||yCilindro<-4){
        incremento = 0;
    }
    yJala = -yCilindro;
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
    case 'b' :
        yCilindro = yCilindro-incremento;
        break;
    case 'n' :
        yCilindro = yCilindro+incremento;
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
