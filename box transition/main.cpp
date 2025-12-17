#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>

GLfloat positionA = -1.2f;
GLfloat positionB =  1.2f;
GLfloat speed = 0.05f;

void drawBoxA() {
    glPushMatrix();
    glTranslatef(positionA, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f( 0.2f,  0.2f);
        glVertex2f(-0.2f,  0.2f);
    glEnd();
    glPopMatrix();
}

void drawBoxB() {
    glPushMatrix();
    glTranslatef(positionB, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(-0.2f, -0.6f);
        glVertex2f( 0.2f, -0.6f);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawBoxA();
    drawBoxB();

    glFlush();
}

void updateA(int value) {
    positionA += speed;
    if (positionA > 1.3f)
        positionA = -1.3f;

    glutPostRedisplay();
    glutTimerFunc(100, updateA, 0);
}

void updateB(int value) {
    positionB -= speed;
    if (positionB < -1.3f)
        positionB = 1.3f;

    glutPostRedisplay();
    glutTimerFunc(100, updateB, 0);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Two Boxes Opposite Direction");

    init();
    glutDisplayFunc(display);

    glutTimerFunc(100, updateA, 0);
    glutTimerFunc(100, updateB, 0);

    glutMainLoop();
    return 0;
}
