#include <windows.h>
#include <GL/glut.h>
#include <math.h>

void circle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++)
    {
        glColor3f(r,g,b);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}


void lampPost() {

    glBegin(GL_QUADS);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.52, 0.00);
    glVertex2f(-0.48, 0.00);
    glVertex2f(-0.48, 0.02);
    glVertex2f(-0.52, 0.02);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(-0.50, 0.02);
    glVertex2f(-0.49, 0.02);
    glVertex2f(-0.49, 0.35);
    glVertex2f(-0.50, 0.35);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(-0.50, 0.35);
    glVertex2f(-0.40, 0.35);
    glVertex2f(-0.40, 0.34);
    glVertex2f(-0.50, 0.34);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-0.41, 0.34);
    glVertex2f(-0.37, 0.34);
    glVertex2f(-0.36, 0.30);
    glVertex2f(-0.42, 0.30);
    glEnd();


    circle(0.02, -0.39, 0.28, 1.0, 1.0, 0.2);
}



void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    lampPost();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("OpenGL Setup");
    glutInitWindowSize(320, 320);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
