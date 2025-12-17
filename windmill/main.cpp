#include <windows.h>
#include <GL/glut.h>
#include <math.h>

float angle = 0.0f;

void circle(float radius, float xc, float yc, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 200; i++)
    {
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 200;
        glVertex2f(radius * cos(A) + xc, radius * sin(A) + yc);
    }
    glEnd();
}

void tower()
{
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, -0.5f);
        glVertex2f(0.1f, -0.5f);
        glVertex2f(0.1f, 0.3f);
        glVertex2f(-0.1f, 0.3f);
    glEnd();

    glColor3ub(238, 75, 43);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.15f, 0.3f);
        glVertex2f(0.15f, 0.3f);
        glVertex2f(0.0f, 0.45f);
    glEnd();

    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, -0.5f);
        glVertex2f(0.04f, -0.5f);
        glVertex2f(0.04f, -0.3f);
        glVertex2f(-0.04f, -0.3f);
    glEnd();

    circle(0.03f, 0.0f, 0.35f, 0.0f, 0.0f, 0.0f);
}

void blade(float xy)
{
    glPushMatrix();
    glTranslatef(0.0f, 0.35f, 0.0f);
    glRotatef(angle + xy, 0.0f, 0.0f, 1.0f);

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.04f);
        glVertex2f(0.30f, 0.015f);
        glVertex2f(0.42f, 0.005f);
        glVertex2f(0.42f, -0.005f);
        glVertex2f(0.30f, -0.015f);
        glVertex2f(0.0f, -0.04f);
    glEnd();

    glPopMatrix();
}

void display()
{
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.196f, 0.804f, 0.196f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.5f);
        glVertex2f(-1.0f, -0.5f);
    glEnd();

    tower();

    blade(0.0f);
    blade(120.0f);
    blade(240.0f);

    glutSwapBuffers();
}

void update(int value)
{
    angle += 2.0f;
    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Windmill Animation");

    glutDisplayFunc(display);
    glutTimerFunc(20, update, 0);

    glutMainLoop();
    return 0;
}
