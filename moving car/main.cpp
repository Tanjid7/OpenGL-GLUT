#include <windows.h>
#include <GL/glut.h>
#include <math.h>

GLfloat pos = -1.2f ;
GLfloat speed = 0.015f ;
float angle = 0.0f;

void circle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
    {
        glColor3f(r,g,b);
        float pi = 3.1416f;
        float A = (i*2*pi)/200;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x+xc, y+yc);
    }
    glEnd();
}

void wheel(float xc, float yc)
{
    glPushMatrix();
    glTranslatef(xc, yc, 0.0f);
    glRotatef(angle, 0, 0, 1);


    circle(0.08f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);


    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
        glVertex2f(-0.08f, 0.0f); glVertex2f(0.08f, 0.0f);
        glVertex2f(0.0f, -0.08f); glVertex2f(0.0f, 0.08f);
        glVertex2f(-0.06f, -0.06f); glVertex2f(0.06f, 0.06f);
        glVertex2f(-0.06f, 0.06f); glVertex2f(0.06f, -0.06f);
    glEnd();

    glPopMatrix();
}

void car()
{

    glColor3f(0.2f, 0.6f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, -0.25f);
        glVertex2f( 0.6f, -0.25f);
        glVertex2f( 0.6f, -0.05f);
        glVertex2f(-0.6f, -0.05f);
    glEnd();


    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.05f);
        glVertex2f( 0.3f, -0.05f);
        glVertex2f( 0.15f, 0.15f);
        glVertex2f(-0.3f, 0.15f);
    glEnd();


    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.32f, -0.02f);
        glVertex2f(-0.05f, -0.02f);
        glVertex2f(-0.12f,  0.12f);
        glVertex2f(-0.30f,  0.12f);
    glEnd();


    glBegin(GL_QUADS);
        glVertex2f( 0.00f, -0.02f);
        glVertex2f( 0.22f, -0.02f);
        glVertex2f( 0.15f,  0.12f);
        glVertex2f( 0.00f,  0.12f);
    glEnd();


    wheel(-0.35f, -0.27f);
    wheel( 0.35f, -0.27f);
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix() ;
    glTranslatef(pos, 0.0 , 0.0) ;

    car();

    glPopMatrix() ;

    glFlush();
}

void update(int value)
{
    angle += 5.0f;
    pos += speed ;

    if(pos > 1.8f) pos = -1.8f ;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600,600);
    glutCreateWindow("Rotation Animation");
    glutDisplayFunc(display);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 0;
}
