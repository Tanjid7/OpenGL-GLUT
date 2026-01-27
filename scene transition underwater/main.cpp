#include <math.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>

float sunY = -1.0f;
bool sunRising = true;
bool isDay = true;
int currentScenario = 1;
int autoSwitchTimer = 0;

float vehiclePos = -1.6f;
bool vanStopped = false;
bool manualLights = false;

float subPos = -1.2f;
float fishPos = 1.5f;
float crabPos = -1.0f;
float jellyY = 0.0f;
bool jellyUp = true;
int subColorState = 0;
bool showBubbles = false;
float bubbleY = 0.0f;

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

void drawRect(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y); glVertex2f(x + width, y);
    glVertex2f(x + width, y + height); glVertex2f(x, y + height);
    glEnd();
}

void drawCelestial() {
    glPushMatrix(); glTranslatef(0.0f, sunY, 0.0f);
    glColor3f(1.0f, 0.9f, 0.0f); drawCircle(0.12f, 30); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, -sunY - 0.8f, 0.0f);
    glColor3f(0.9f, 0.9f, 1.0f); drawCircle(0.1f, 30); glPopMatrix();
}

void drawStars() {
    if(!isDay) {
        glColor3f(1.0f, 1.0f, 1.0f); glPointSize(2.0f);
        glBegin(GL_POINTS);
        glVertex2f(-0.8f, 0.8f); glVertex2f(0.7f, 0.85f);
        glVertex2f(-0.5f, 0.6f); glVertex2f(0.2f, 0.9f);
        glVertex2f( 0.6f, 0.5f); glVertex2f(-0.2f, 0.7f);
        glVertex2f( 0.0f, 0.85f); glVertex2f(-0.9f, 0.5f);
        glVertex2f( 0.85f, 0.6f); glVertex2f(-0.65f, 0.65f);
        glEnd();
    }
}

void drawStreet() {
    glColor3f(0.3f, 0.3f, 0.35f); drawRect(-1.0f, -0.22f, 2.0f, 0.02f);
    glColor3f(0.7f, 0.7f, 0.7f);  drawRect(-1.0f, -0.38f, 2.0f, 0.16f);
    glColor3f(0.5f, 0.5f, 0.5f);  drawRect(-1.0f, -0.40f, 2.0f, 0.02f);
    if(isDay) glColor3f(0.2f, 0.2f, 0.2f); else glColor3f(0.1f, 0.1f, 0.1f);
    drawRect(-1.0f, -1.0f, 2.0f, 0.6f);
    glColor3f(0.8f, 0.7f, 0.0f);
    drawRect(-0.9f, -0.7f, 0.2f, 0.02f); drawRect(-0.5f, -0.7f, 0.2f, 0.02f);
    drawRect(-0.1f, -0.7f, 0.2f, 0.02f); drawRect( 0.3f, -0.7f, 0.2f, 0.02f);
    drawRect( 0.7f, -0.7f, 0.2f, 0.02f);
}

void drawStreetLight(float x) {
    glPushMatrix(); glTranslatef(x, -0.2f, 0.0f); glScalef(0.7f, 0.7f, 1.0f);
    glColor3f(0.5f, 0.5f, 0.55f); drawRect(-0.025f, 0.0f, 0.05f, 0.06f);
    glColor3f(0.15f, 0.15f, 0.2f); drawRect(-0.015f, 0.06f, 0.03f, 0.60f);
    glBegin(GL_QUADS);
    glVertex2f(-0.015f, 0.64f); glVertex2f( 0.015f, 0.66f);
    glVertex2f(-0.25f, 0.72f); glVertex2f(-0.25f, 0.69f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.22f, 0.71f); glVertex2f(-0.35f, 0.68f);
    glVertex2f(-0.34f, 0.65f); glVertex2f(-0.20f, 0.68f);
    glEnd();
    if(manualLights || !isDay) glColor3f(1.0f, 1.0f, 0.9f); else glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, 0.68f); glVertex2f(-0.32f, 0.66f);
    glVertex2f(-0.31f, 0.65f); glVertex2f(-0.23f, 0.66f);
    glEnd();
    glPopMatrix();
}

void drawSupermarket(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    if(isDay) glColor3f(0.92f, 0.92f, 0.88f); else glColor3f(0.5f, 0.5f, 0.45f);
    drawRect(0.0f, 0.0f, 1.0f, 0.6f);
    if(isDay) glColor3f(0.0f, 0.4f, 0.2f); else glColor3f(0.0f, 0.2f, 0.1f);
    drawRect(-0.02f, 0.55f, 1.04f, 0.08f);
    if(isDay) glColor3f(0.8f, 0.8f, 0.8f); else glColor3f(0.3f, 0.3f, 0.3f);
    drawRect(0.35f, 0.63f, 0.3f, 0.15f);
    if(isDay) glColor3f(1.0f, 0.6f, 0.0f); else glColor3f(1.0f, 0.8f, 0.0f);
    drawRect(0.37f, 0.66f, 0.26f, 0.02f); drawRect(0.37f, 0.70f, 0.26f, 0.02f);
    drawRect(0.37f, 0.74f, 0.26f, 0.02f);
    glColor3f(0.2f, 0.2f, 0.2f); drawRect(0.39f, 0.05f, 0.22f, 0.26f);
    if(isDay) glColor3f(0.6f, 0.8f, 1.0f); else glColor3f(0.9f, 0.9f, 0.7f);
    drawRect(0.40f, 0.06f, 0.09f, 0.24f); drawRect(0.51f, 0.06f, 0.09f, 0.24f);
    float ay = 0.32f; float ah = 0.08f;
    if(isDay) glColor3f(0.8f, 0.2f, 0.2f); else glColor3f(0.4f, 0.1f, 0.1f);
    drawRect(0.35f, ay, 0.03f, ah); drawRect(0.41f, ay, 0.03f, ah);
    drawRect(0.47f, ay, 0.03f, ah); drawRect(0.53f, ay, 0.03f, ah);
    drawRect(0.59f, ay, 0.03f, ah); drawRect(0.65f, ay, 0.03f, ah);
    if(isDay) glColor3f(0.95f, 0.95f, 0.95f); else glColor3f(0.6f, 0.6f, 0.6f);
    drawRect(0.38f, ay, 0.03f, ah); drawRect(0.44f, ay, 0.03f, ah);
    drawRect(0.50f, ay, 0.03f, ah); drawRect(0.56f, ay, 0.03f, ah);
    drawRect(0.62f, ay, 0.03f, ah);
    if(isDay) glColor3f(0.5f, 0.7f, 0.9f); else glColor3f(1.0f, 1.0f, 0.6f);
    drawRect(0.05f, 0.1f, 0.25f, 0.3f); drawRect(0.7f, 0.1f, 0.25f, 0.3f);
    glColor3f(0.3f, 0.3f, 0.3f);
    drawRect(0.04f, 0.08f, 0.27f, 0.02f); drawRect(0.69f, 0.08f, 0.27f, 0.02f);
    glPopMatrix();
}

void drawTallBuilding(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    if(isDay) glColor3f(0.6f, 0.6f, 0.65f); else glColor3f(0.25f, 0.25f, 0.3f);
    drawRect(0.0f, 0.0f, 0.3f, 0.9f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,1.0f,0.0f);
    drawRect(0.05f, 0.7f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(0.1f,0.1f,0.1f);
    drawRect(0.17f, 0.7f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,1.0f,0.0f);
    drawRect(0.05f, 0.5f, 0.08f, 0.1f); drawRect(0.17f, 0.5f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(0.1f,0.1f,0.1f);
    drawRect(0.05f, 0.3f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,1.0f,0.0f);
    drawRect(0.17f, 0.3f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,1.0f,0.0f);
    drawRect(0.05f, 0.1f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(0.1f,0.1f,0.1f);
    drawRect(0.17f, 0.1f, 0.08f, 0.1f);
    glPopMatrix();
}

void drawMediumBuilding(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    if(isDay) glColor3f(0.6f, 0.4f, 0.3f); else glColor3f(0.3f, 0.2f, 0.15f);
    drawRect(0.0f, 0.0f, 0.4f, 0.7f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,0.9f,0.0f);
    drawRect(0.05f, 0.5f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(0.1f,0.1f,0.1f);
    drawRect(0.16f, 0.5f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,0.9f,0.0f);
    drawRect(0.27f, 0.5f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(0.1f,0.1f,0.1f);
    drawRect(0.05f, 0.3f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,0.9f,0.0f);
    drawRect(0.16f, 0.3f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(0.1f,0.1f,0.1f);
    drawRect(0.27f, 0.3f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,0.9f,0.0f);
    drawRect(0.05f, 0.1f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,0.9f,0.0f);
    drawRect(0.16f, 0.1f, 0.08f, 0.1f);
    if(isDay) glColor3f(0.2f,0.3f,0.4f); else glColor3f(1.0f,0.9f,0.0f);
    drawRect(0.27f, 0.1f, 0.08f, 0.1f);
    glPopMatrix();
}

void drawVehicle() {
    glPushMatrix(); glTranslatef(vehiclePos, -0.55f, 0.0f); glScalef(1.4f, 1.4f, 1.0f);
    if(isDay) glColor3f(0.9f, 0.9f, 0.9f); else glColor3f(0.6f, 0.6f, 0.6f);
    drawRect(0.0f, 0.05f, 0.35f, 0.15f); drawRect(0.25f, 0.05f, 0.12f, 0.12f);
    glColor3f(0.2f, 0.4f, 0.8f); drawRect(0.0f, 0.11f, 0.36f, 0.02f);
    glColor3f(0.3f, 0.3f, 0.3f); drawRect(-0.01f, 0.05f, 0.39f, 0.02f);
    glColor3f(0.2f, 0.2f, 0.3f);
    drawRect(0.28f, 0.13f, 0.07f, 0.05f); drawRect(0.02f, 0.13f, 0.05f, 0.04f);
    glColor3f(0.1f, 0.1f, 0.1f); drawRect(0.26f, 0.1f, 0.02f, 0.005f);
    if(isDay) glColor3f(0.8f, 0.0f, 0.0f); else glColor3f(1.0f, 0.0f, 0.0f);
    drawRect(0.0f, 0.13f, 0.015f, 0.04f);
    if(isDay) glColor3f(0.9f, 0.9f, 0.8f); else glColor3f(1.0f, 1.0f, 0.6f);
    drawRect(0.36f, 0.08f, 0.01f, 0.03f);
    glColor3f(0.2f, 0.2f, 0.2f); drawRect(0.36f, 0.06f, 0.01f, 0.015f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix(); glTranslatef(0.08f, 0.05f, 0.0f); drawCircle(0.05f, 12); glPopMatrix();
    glPushMatrix(); glTranslatef(0.28f, 0.05f, 0.0f); drawCircle(0.05f, 12); glPopMatrix();
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix(); glTranslatef(0.08f, 0.05f, 0.0f); drawCircle(0.025f, 8); glPopMatrix();
    glPushMatrix(); glTranslatef(0.28f, 0.05f, 0.0f); drawCircle(0.025f, 8); glPopMatrix();
    glPopMatrix();
}

void drawSand() {
    glColor3f(0.7f, 0.6f, 0.3f); drawRect(-1.0f, -1.0f, 2.0f, 0.3f);
}

void drawSeaweed(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    glColor3f(0.1f, 0.5f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.02f, 0.0f); glVertex2f(0.02f, 0.0f); glVertex2f(-0.05f, 0.2f);
    glVertex2f(0.0f, 0.0f); glVertex2f(0.04f, 0.0f); glVertex2f(0.05f, 0.25f);
    glVertex2f(0.03f, 0.0f); glVertex2f(0.06f, 0.0f); glVertex2f(0.0f, 0.15f);
    glEnd(); glPopMatrix();
}

void drawFish(float x, float y, float r, float g, float b) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(0.08f, 0.0f); glVertex2f(0.04f, 0.04f); glVertex2f(-0.04f, 0.04f);
    glVertex2f(-0.08f, 0.0f); glVertex2f(-0.04f, -0.04f); glVertex2f(0.04f, -0.04f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.08f, 0.0f); glVertex2f(0.12f, 0.05f); glVertex2f(0.12f, -0.05f);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f); drawRect(-0.05f, 0.01f, 0.01f, 0.01f);
    glPopMatrix();
}

void drawCrab(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    glColor3f(0.8f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0.06f, 0.0f); glVertex2f(0.04f, 0.04f); glVertex2f(-0.04f, 0.04f);
    glVertex2f(-0.06f, 0.0f); glVertex2f(-0.04f, -0.04f); glVertex2f(0.04f, -0.04f);
    glEnd();
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.04f, 0.0f); glVertex2f(-0.08f, -0.05f);
    glVertex2f(-0.02f, 0.0f); glVertex2f(-0.04f, -0.06f);
    glVertex2f( 0.02f, 0.0f); glVertex2f( 0.04f, -0.06f);
    glVertex2f( 0.04f, 0.0f); glVertex2f( 0.08f, -0.05f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.05f, 0.03f); glVertex2f(-0.09f, 0.06f); glVertex2f(-0.08f, 0.02f);
    glVertex2f( 0.05f, 0.03f); glVertex2f( 0.09f, 0.06f); glVertex2f( 0.08f, 0.02f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); drawRect(-0.03f, 0.04f, 0.02f, 0.02f); drawRect(0.01f, 0.04f, 0.02f, 0.02f);
    glColor3f(0.0f, 0.0f, 0.0f); drawRect(-0.025f, 0.045f, 0.01f, 0.01f); drawRect(0.015f, 0.045f, 0.01f, 0.01f);
    glPopMatrix();
}

void drawJellyfish(float x, float y) {
    glPushMatrix(); glTranslatef(x, y, 0.0f);
    glColor4f(1.0f, 0.6f, 0.8f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f, 0.0f); glVertex2f(-0.07f, 0.04f); glVertex2f(-0.05f, 0.06f);
    glVertex2f( 0.00f, 0.08f); glVertex2f( 0.05f, 0.06f); glVertex2f( 0.07f, 0.04f);
    glVertex2f( 0.08f, 0.0f);
    glEnd();
    glColor3f(0.9f, 0.5f, 0.7f); glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(-0.04f, 0.0f); glVertex2f(-0.05f, -0.1f);
    glVertex2f(-0.02f, 0.0f); glVertex2f(-0.01f, -0.12f);
    glVertex2f( 0.0f, 0.0f);  glVertex2f( 0.0f, -0.08f);
    glVertex2f( 0.02f, 0.0f); glVertex2f( 0.03f, -0.11f);
    glVertex2f( 0.04f, 0.0f); glVertex2f( 0.05f, -0.09f);
    glEnd(); glPopMatrix();
}

void drawSubmarine() {
    glPushMatrix(); glTranslatef(subPos, -0.5f, 0.0f);
    if(subColorState == 0) glColor3f(1.0f, 0.9f, 0.0f);
    else if(subColorState == 1) glColor3f(0.9f, 0.2f, 0.2f);
    else glColor3f(0.2f, 0.8f, 0.3f);
    drawCircle(0.15f, 30);
    glPushMatrix(); glScalef(1.5f, 0.8f, 1.0f); drawCircle(0.15f, 30); glPopMatrix();
    drawRect(-0.05f, 0.1f, 0.1f, 0.08f);
    drawRect(-0.02f, 0.18f, 0.02f, 0.05f); drawRect(0.0f, 0.21f, 0.04f, 0.02f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25f, 0.0f); glVertex2f(-0.35f, 0.05f); glVertex2f(-0.35f, -0.05f);
    glEnd();
    glColor3f(0.6f, 0.8f, 1.0f);
    glPushMatrix(); glTranslatef(-0.1f, 0.0f, 0.0f); drawCircle(0.04f, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, 0.0f, 0.0f); drawCircle(0.04f, 10); glPopMatrix();
    glPushMatrix(); glTranslatef(0.1f, 0.0f, 0.0f); drawCircle(0.04f, 10); glPopMatrix();
    if(showBubbles) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix(); glTranslatef(0.2f, bubbleY, 0.0f); drawCircle(0.02f, 8); glPopMatrix();
        glPushMatrix(); glTranslatef(0.25f, bubbleY + 0.05f, 0.0f); drawCircle(0.015f, 8); glPopMatrix();
    }
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if(currentScenario == 1) {
        if (sunY > -0.2f) { isDay = true; glClearColor(0.5f, 0.7f, 1.0f, 1.0f); }
        else { isDay = false; glClearColor(0.05f, 0.05f, 0.15f, 1.0f); }
    } else { glClearColor(0.0f, 0.2f, 0.4f, 1.0f); }
    glClear(GL_COLOR_BUFFER_BIT);
    if(currentScenario == 1) {
        drawStars(); drawCelestial();
        drawTallBuilding(-0.95f, -0.2f); drawMediumBuilding(-0.6f, -0.2f);
        drawSupermarket(-0.1f, -0.2f); drawStreet();
        drawStreetLight(-0.6f); drawStreetLight( 0.1f); drawStreetLight( 0.8f);
        drawVehicle();
    } else {
        drawSand();
        drawSeaweed(-0.8f, -0.7f); drawSeaweed(-0.7f, -0.75f);
        drawSeaweed(0.2f, -0.7f); drawSeaweed(0.8f, -0.8f);
        drawCrab(crabPos, -0.75f); drawJellyfish(0.5f, jellyY);
        drawSubmarine();
        drawFish(fishPos, 0.2f, 1.0f, 0.6f, 0.0f);
        drawFish(fishPos + 0.3f, 0.4f, 0.8f, 0.2f, 0.8f);
        drawFish(fishPos - 0.2f, 0.6f, 0.0f, 0.8f, 0.8f);
    }
    glutSwapBuffers();
}

void update(int value) {
    if (sunRising) { sunY += 0.005f; if (sunY > 0.9f) sunRising = false; }
    else { sunY -= 0.005f; if (sunY < -1.5f) sunRising = true; }
    if(!vanStopped) { vehiclePos += 0.007f; if (vehiclePos > 1.5f) vehiclePos = -1.6f; }
    subPos += 0.004f; if (subPos > 1.3f) subPos = -1.3f;
    fishPos -= 0.003f; if (fishPos < -1.5f) fishPos = 1.5f;
    crabPos += 0.001f; if (crabPos > 1.1f) crabPos = -1.1f;
    if(jellyUp) { jellyY += 0.002f; if(jellyY > 0.3f) jellyUp = false; }
    else { jellyY -= 0.002f; if(jellyY < -0.3f) jellyUp = true; }
    if(showBubbles) { bubbleY += 0.01f; if(bubbleY > 0.5f) { showBubbles = false; bubbleY = 0.0f; } }
    autoSwitchTimer++;
    if(autoSwitchTimer > 600) { currentScenario = (currentScenario == 1) ? 2 : 1; autoSwitchTimer = 0; }
    glutPostRedisplay(); glutTimerFunc(16, update, 0);
}

void handleKey(unsigned char key, int x, int y) {
    if(key == '1') { currentScenario = 1; autoSwitchTimer = 0; }
    if(key == '2') { currentScenario = 2; autoSwitchTimer = 0; }
    if(key == 'l') manualLights = !manualLights;
    if(key == 'c') subColorState = (subColorState + 1) % 3;
}

void handleMouse(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(currentScenario == 1) vanStopped = !vanStopped;
        else showBubbles = true;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Merged: City & Ocean (No Loops in S2)");
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(handleKey);
    glutMouseFunc(handleMouse);
    glutMainLoop();
    return 0;
}
