#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>

int currentScene = 1;

void drawCircle(float r, int segments) {
    glBegin(GL_POLYGON);
    for(int i = 0; i < segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

float sunY1 = -1.0f;
bool sunRising1 = true;
float cloudPos1 = 0.0f;
float carX1 = -0.4f;
bool isDay1 = true;
bool isAnimate1 = true;

void drawGround1() {
    glColor3f(0.5f, 0.5f, 0.5f);
    if(!isDay1) glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f( 1.0f, -0.2f);
    glVertex2f( 1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    if(!isDay1) glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.4f);
    glVertex2f( 1.0f, -0.4f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    if(!isDay1) glColor3f(0.5f, 0.5f, 0.5f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.7f);
    glVertex2f(-0.7f, -0.7f);
    glVertex2f(-0.5f, -0.7f);
    glVertex2f(-0.2f, -0.7f);
    glVertex2f( 0.0f, -0.7f);
    glVertex2f( 0.3f, -0.7f);
    glVertex2f( 0.5f, -0.7f);
    glVertex2f( 0.8f, -0.7f);
    glEnd();
}

void drawCar1() {
    glPushMatrix();
    glTranslatef(carX1, -0.55f, 0.0f);

    if (isDay1) glColor3f(0.2f, 0.4f, 0.7f);
    else        glColor3f(0.1f, 0.2f, 0.4f);

    glBegin(GL_QUADS);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f( 0.2f, 0.0f);
    glVertex2f( 0.2f, 0.12f);
    glVertex2f(-0.2f, 0.12f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.12f, 0.12f);
    glVertex2f( 0.12f, 0.12f);
    glVertex2f( 0.08f, 0.22f);
    glVertex2f(-0.08f, 0.22f);
    glEnd();

    if (isDay1) glColor3f(0.6f, 0.8f, 0.9f);
    else        glColor3f(0.1f, 0.1f, 0.2f);

    glBegin(GL_QUADS);
    glVertex2f(-0.09f, 0.13f);
    glVertex2f( 0.09f, 0.13f);
    glVertex2f( 0.06f, 0.20f);
    glVertex2f(-0.06f, 0.20f);
    glEnd();

    if (!isDay1) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.08f);
        glVertex2f(0.5f, 0.15f);
        glVertex2f(0.5f, 0.0f);
        glEnd();

        glColor3f(1.0f, 0.9f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(0.18f, 0.05f);
        glVertex2f(0.20f, 0.05f);
        glVertex2f(0.20f, 0.10f);
        glVertex2f(0.18f, 0.10f);
        glEnd();
    }

    glPushMatrix();
    glTranslatef(-0.12f, 0.0f, 0.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(0.05f, 20);
    if(isDay1) glColor3f(0.7f, 0.7f, 0.7f);
    else glColor3f(0.4f, 0.4f, 0.4f);
    drawCircle(0.025f, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.12f, 0.0f, 0.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(0.05f, 20);
    if(isDay1) glColor3f(0.7f, 0.7f, 0.7f);
    else glColor3f(0.4f, 0.4f, 0.4f);
    drawCircle(0.025f, 15);
    glPopMatrix();

    glPopMatrix();
}

void drawBuilding1(float x, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    if(!isDay1) glColor3f(r*0.3f, g*0.3f, b*0.3f);

    glBegin(GL_QUADS);
    glVertex2f(x, -0.2f);
    glVertex2f(x + width, -0.2f);
    glVertex2f(x + width, -0.2f + height);
    glVertex2f(x, -0.2f + height);
    glEnd();

    if(isDay1) glColor3f(0.2f, 0.3f, 0.4f);
    else glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.02f, -0.15f);
    glVertex2f(x + 0.07f, -0.15f);
    glVertex2f(x + 0.07f, -0.10f);
    glVertex2f(x + 0.02f, -0.10f);
    glEnd();

    if(isDay1) glColor3f(0.2f, 0.3f, 0.4f);
    else glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.09f, -0.15f);
    glVertex2f(x + 0.14f, -0.15f);
    glVertex2f(x + 0.14f, -0.10f);
    glVertex2f(x + 0.09f, -0.10f);
    glEnd();

    if(isDay1) glColor3f(0.2f, 0.3f, 0.4f);
    else glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.02f, -0.05f);
    glVertex2f(x + 0.07f, -0.05f);
    glVertex2f(x + 0.07f,  0.00f);
    glVertex2f(x + 0.02f,  0.00f);
    glEnd();

    if(isDay1) glColor3f(0.2f, 0.3f, 0.4f);
    else glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.09f, -0.05f);
    glVertex2f(x + 0.14f, -0.05f);
    glVertex2f(x + 0.14f,  0.00f);
    glVertex2f(x + 0.09f,  0.00f);
    glEnd();

    if(isDay1) glColor3f(0.2f, 0.3f, 0.4f);
    else glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.02f, 0.05f);
    glVertex2f(x + 0.07f, 0.05f);
    glVertex2f(x + 0.07f, 0.10f);
    glVertex2f(x + 0.02f, 0.10f);
    glEnd();

    if(isDay1) glColor3f(0.2f, 0.3f, 0.4f);
    else glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x + 0.09f, 0.05f);
    glVertex2f(x + 0.14f, 0.05f);
    glVertex2f(x + 0.14f, 0.10f);
    glVertex2f(x + 0.09f, 0.10f);
    glEnd();
}

void drawStreetLight(float x) {
    glPushMatrix();
    glTranslatef(x, -0.2f, 0.0f);

    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.1f, 0.4f);
    glEnd();

    if(!isDay1) glColor3f(1.0f, 1.0f, 0.8f);
    else glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.4f);
    glVertex2f(0.12f, 0.4f);
    glVertex2f(0.14f, 0.35f);
    glVertex2f(0.06f, 0.35f);
    glEnd();

    glPopMatrix();
}

void drawCity1() {
    drawBuilding1(-0.9f, 0.25f, 0.7f, 0.4f, 0.4f, 0.5f);
    drawBuilding1(-0.2f, 0.3f, 0.9f, 0.5f, 0.3f, 0.3f);
    drawBuilding1( 0.4f, 0.25f, 0.6f, 0.3f, 0.4f, 0.3f);
    drawBuilding1(-0.6f, 0.2f, 0.5f, 0.6f, 0.6f, 0.65f);
    drawBuilding1( 0.15f, 0.2f, 0.4f, 0.7f, 0.7f, 0.6f);
    drawBuilding1( 0.7f, 0.25f, 0.8f, 0.5f, 0.5f, 0.6f);

    drawStreetLight(-0.5f);
    drawStreetLight( 0.0f);
    drawStreetLight( 0.5f);
}

void drawCloud1(float offset) {
    glColor3f(1.0f, 1.0f, 1.0f);
    if(!isDay1) glColor3f(0.3f, 0.3f, 0.3f);

    glPushMatrix();
    glTranslatef(cloudPos1 + offset, 0.7f, 0.0f);
    drawCircle(0.08f, 20);
    glTranslatef(0.1f, 0.0f, 0.0f);
    drawCircle(0.08f, 20);
    glPopMatrix();
}

void drawSky1() {
    glPushMatrix();
    glTranslatef(0.6f, sunY1, 0.0f);
    glColor3f(1.0f, 0.9f, 0.0f);
    drawCircle(0.1f, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.6f, -sunY1 - 0.6f, 0.0f);
    glColor3f(0.9f, 0.9f, 0.9f);
    drawCircle(0.08f, 30);
    glPopMatrix();
    drawCloud1(-0.5f);
    drawCloud1(0.2f);
}

void displayScenario1() {
    if (sunY1 > -0.2f) {
        isDay1 = true;
        glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
    } else {
        isDay1 = false;
        glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    drawSky1();
    drawGround1();
    drawCity1();
    drawCar1();
}

void updateScenario1() {
    if (!isAnimate1) return;
    if (sunRising1) {
        sunY1 += 0.005f;
        if (sunY1 > 0.9f) sunRising1 = false;
    } else {
        sunY1 -= 0.005f;
        if (sunY1 < -1.5f) sunRising1 = true;
    }
    cloudPos1 += 0.002f;
    if (cloudPos1 > 1.5f) cloudPos1 = -1.5f;
    carX1 += 0.015f;
    if (carX1 > 1.2f) carX1 = -1.2f;
}

float sunY2 = -1.0f;
bool sunRising2 = true;
float busX2 = 0.4f;
bool isTrafficRed = true;
bool isDay2 = true;

void drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawGround2() {
    glColor3f(0.15f, 0.15f, 0.15f);
    drawRect(-1.0f, -1.0f, 1.0f, -0.3f);
    glColor3f(0.6f, 0.6f, 0.6f);
    drawRect(-1.0f, -0.3f, 1.0f, -0.2f);
    glColor3f(0.9f, 0.8f, 0.0f);
    drawRect(-1.0f, -0.62f, 1.0f, -0.60f);
    drawRect(-1.0f, -0.66f, 1.0f, -0.64f);
}

void drawSkyline2() {
    glColor3f(0.2f, 0.2f, 0.25f);
    drawRect(-0.8f, -0.2f, -0.4f, 0.6f);
    drawRect(-0.2f, -0.2f,  0.2f, 0.5f);
    drawRect( 0.5f, -0.2f,  0.8f, 0.7f);

    glColor3f(0.3f, 0.3f, 0.4f);
    drawRect(-0.95f, -0.2f, -0.65f, 0.7f);

    if(isDay2) glColor3f(0.5f, 0.7f, 0.9f);
    else glColor3f(1.0f, 1.0f, 0.0f);
    drawRect(-0.90f, -0.1f, -0.85f, 0.0f);
    drawRect(-0.75f, -0.1f, -0.70f, 0.0f);
    drawRect(-0.90f,  0.1f, -0.85f, 0.2f);
    drawRect(-0.75f,  0.1f, -0.70f, 0.2f);
    drawRect(-0.90f,  0.3f, -0.85f, 0.4f);
    drawRect(-0.75f,  0.3f, -0.70f, 0.4f);
    drawRect(-0.90f,  0.5f, -0.85f, 0.6f);
    drawRect(-0.75f,  0.5f, -0.70f, 0.6f);

    glColor3f(0.6f, 0.4f, 0.3f);
    drawRect(-0.55f, -0.2f, 0.15f, 0.6f);

    if(isDay2) glColor3f(0.8f, 0.9f, 1.0f);
    else glColor3f(0.9f, 0.9f, 0.5f);
    drawRect(-0.50f, 0.0f, -0.40f, 0.1f);
    drawRect(-0.30f, 0.0f, -0.20f, 0.1f);
    drawRect(-0.10f, 0.0f, 0.00f, 0.1f);
    drawRect(-0.50f, 0.2f, -0.40f, 0.3f);
    drawRect(-0.30f, 0.2f, -0.20f, 0.3f);
    drawRect(-0.10f, 0.2f, 0.00f, 0.3f);
    drawRect(-0.50f, 0.4f, -0.40f, 0.5f);
    drawRect(-0.30f, 0.4f, -0.20f, 0.5f);
    drawRect(-0.10f, 0.4f, 0.00f, 0.5f);

    glColor3f(0.2f, 0.5f, 0.6f);
    drawRect(0.3f, -0.2f, 0.8f, 0.85f);

    if(isDay2) glColor3f(0.8f, 0.9f, 1.0f);
    else glColor3f(0.9f, 0.8f, 0.4f);
    drawRect(0.35f, 0.0f, 0.45f, 0.15f);
    drawRect(0.5f, 0.0f, 0.6f, 0.15f);
    drawRect(0.65f, 0.0f, 0.75f, 0.15f);
    drawRect(0.35f, 0.25f, 0.45f, 0.40f);
    drawRect(0.5f, 0.25f, 0.6f, 0.40f);
    drawRect(0.65f, 0.25f, 0.75f, 0.40f);
    drawRect(0.35f, 0.50f, 0.45f, 0.65f);
    drawRect(0.5f, 0.50f, 0.6f, 0.65f);
    drawRect(0.65f, 0.50f, 0.75f, 0.65f);
}

void drawBus2() {
    glPushMatrix();
    glTranslatef(busX2, -0.5f, 0.0f);

    glColor3f(0.9f, 0.7f, 0.0f);
    drawRect(-0.25f, 0.0f, 0.25f, 0.25f);

    glColor3f(0.4f, 0.7f, 1.0f);
    drawRect(-0.20f, 0.12f, -0.05f, 0.22f);
    drawRect( 0.05f, 0.12f,  0.20f, 0.22f);

    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(-0.15f, 0.0f, 0.0f);
    drawCircle(0.06f, 15);
    glPopMatrix();
    glPushMatrix();
    glTranslatef( 0.15f, 0.0f, 0.0f);
    drawCircle(0.06f, 15);
    glPopMatrix();

    glPopMatrix();
}

void drawTrafficLight2() {
    glPushMatrix();
    glTranslatef(0.2f, -0.2f, 0.0f);

    glColor3f(0.2f, 0.2f, 0.2f);
    drawRect(-0.02f, 0.0f, 0.02f, 0.5f);

    glColor3f(0.1f, 0.1f, 0.1f);
    drawRect(-0.05f, 0.5f, 0.05f, 0.8f);

    if(isTrafficRed) glColor3f(1.0f, 0.0f, 0.0f);
    else glColor3f(0.3f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.73f, 0.0f);
    drawCircle(0.03f, 10);
    glPopMatrix();

    if(!isTrafficRed) glColor3f(0.0f, 1.0f, 0.0f);
    else glColor3f(0.0f, 0.3f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.57f, 0.0f);
    drawCircle(0.03f, 10);
    glPopMatrix();

    glPopMatrix();
}

void drawSky2() {
    glPushMatrix();
    glTranslatef(0.0f, sunY2, 0.0f);
    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(0.12f, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, -sunY2 - 0.6f, 0.0f);
    glColor3f(0.9f, 0.9f, 0.9f);
    drawCircle(0.1f, 30);
    glPopMatrix();
}

void updateScenario2() {
    if (sunRising2) {
        sunY2 += 0.003f;
        if (sunY2 > 0.9f) sunRising2 = false;
    } else {
        sunY2 -= 0.003f;
        if (sunY2 < -1.5f) sunRising2 = true;
    }

    busX2 -= 0.01f;
    if (busX2 < -1.2f) busX2 = 1.2f;
}

void displayScenario2() {
    if (sunY2 > -0.2f) {
        isDay2 = true;
        glClearColor(0.5f, 0.6f, 0.8f, 1.0f);
    } else {
        isDay2 = false;
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky2();
    drawGround2();
    drawSkyline2();
    drawTrafficLight2();
    drawBus2();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') currentScene = 1;
    if (key == '2') currentScene = 2;

    if (currentScene == 1) {
        if (key == ' ') isAnimate1 = !isAnimate1;
    }
    if (currentScene == 2) {
        if (key == 'w' || key == 'W') isTrafficRed = !isTrafficRed;
    }
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (currentScene == 1 && button == GLUT_LEFT_BUTTON) {
            if (sunY1 > -0.2f) sunY1 = -1.0f;
            else sunY1 = 0.5f;
        }
    }
}

void display() {
    if (currentScene == 1) displayScenario1();
    else displayScenario2();
    glutSwapBuffers();
}

void update(int value) {
    if (currentScene == 1) updateScenario1();
    else updateScenario2();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Two Cities: Scene 1 & Downtown Scene 2");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
