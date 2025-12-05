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

void tree() {
    glBegin(GL_QUADS);
    glColor3f(0.55, 0.27, 0.07);
    glVertex2f(0.45, 0.001);
    glVertex2f(0.52, 0.001);
    glVertex2f(0.52, 0.25);
    glVertex2f(0.45, 0.25);
    glEnd();

    circle(0.08, 0.42, 0.28, 0.0, 0.7, 0.0);
    circle(0.08, 0.55, 0.28, 0.0, 0.7, 0.0);
    circle(0.09, 0.50, 0.38, 0.0, 0.8, 0.0);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    tree();

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



