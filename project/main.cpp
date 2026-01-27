#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>

float jetmov = -4.0f;
float carmov = -3.0f;
float shipmov = -2.0f;
float smokescal = 1.0f;
float jetbase = 0.03f;
float jetc = 0.03f;
int jettimer = 0;
bool shipmoving = true;
bool carmoving = true;
bool s_light = true;
bool flashh = false;
int flashtimer = 0;
float skyr = 0.5f;
float skyg = 0.8f;
float skyb = 1.0f;
bool isDay = true;
float sunY = 1.6f;
float moonY = -1.6f;
float lightopa = 0.0f;
float bombX = 0.0f;
float bombY = 1.6f;
bool bombfall = false;
bool explode = false;
float exploscale = 0.0f;
float lightangle = 0.0f;
float lightDir = 1.0f;
float clx1 = -2.5f;
float clx2 = 0.5f;

void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);  // Set the position to start drawing text
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);  // Render each character
    }
}

void circle(float radius, float xc, float yc, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 200;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void circleAlpha(float radius, float xc, float yc, float r, float g, float b, float a) {
    glBegin(GL_POLYGON);
    glColor4f(r, g, b, a);
    for (int i = 0; i < 200; i++) {
        float pi = 3.1416f;
        float A = (i * 2 * pi) / 200;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void layer(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void text() {


    //glColor3f(1.0f, 1.0f, 1.0f);
    //renderText(-0.5f, 1.85f, "WAR SCENARIO");


    glColor3f(1.0f, 1.0f, 0.0f);
    if (isDay) renderText(-1.9f, 1.85f, "Time: DAY ('N')");
    else       renderText(-1.9f, 1.85f, "Time: NIGHT ('N')");

    if (s_light) renderText(-1.9f, 1.75f, "Lights: ON ('L')");
    else         renderText(-1.9f, 1.75f, "Lights: OFF ('L')");

    if (shipmoving) renderText(-1.9f, 1.65f, "Ship: MOVING ('W')");
    else              renderText(-1.9f, 1.65f, "Ship: STOPPED ('W')");

    if (carmoving) renderText(-1.9f, 1.55f, "Car: MOVING ('C')");
    else             renderText(-1.9f, 1.55f, "Car: STOPPED ('C')");

    glColor3f(0.0f, 1.0f, 0.0f);
    renderText(0.8f, 1.85f, "MOUSE CONTROLS");

    if (bombfall || explode) glColor3f(1.0f, 0.0f, 0.0f);
    else                            glColor3f(0.0f, 1.0f, 0.0f);
    renderText(0.8f, 1.75f, "L-Click: Bomb");

    if (jettimer > 0) glColor3f(1.0f, 0.5f, 0.0f);
    else                   glColor3f(0.0f, 1.0f, 0.0f);
    renderText(0.8f, 1.65f, "R-Click: Boost");
}


void drawExplosion() {
    if (explode) {
        glPushMatrix();
        glTranslatef(bombX, 0.8f, 0.0f);
        glScalef(exploscale, exploscale, 1.0f);

        circle(0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        circle(0.2f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f);
        circle(0.1f, 0.0f, 0.0f, 1.0f, 1.0f, 0.8f);

        glPopMatrix();
    }
}

void drawStars() {
    if (!isDay) {
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-1.5f, 1.8f);
        glVertex2f(-0.5f, 1.7f);
        glVertex2f(0.5f, 1.8f);
        glVertex2f(1.5f, 1.7f);
        glVertex2f(0.8f, 1.6f);
        glVertex2f(-1.0f, 1.9f);
        glVertex2f(0.0f, 1.9f);
        glVertex2f(1.0f, 1.9f);
        glVertex2f(-1.2f, 1.5f);
        glVertex2f(-0.2f, 1.6f);
        glEnd();
    }
}

void drawClouds() {
    float clcolor = isDay ? 0.9f : 0.3f;
    glPushMatrix();
    glTranslatef(clx1, 1.5f, 0.0f);
    circle(0.15f, 0.0f, 0.0f, clcolor, clcolor, clcolor);
    circle(0.2f, 0.15f, 0.0f, clcolor, clcolor, clcolor);
    circle(0.15f, 0.3f, 0.0f, clcolor, clcolor, clcolor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(clx2, 1.7f, 0.0f);
    glScalef(0.7f, 0.7f, 1.0f);
    circle(0.15f, 0.0f, 0.0f, clcolor, clcolor, clcolor);
    circle(0.2f, 0.15f, 0.0f, clcolor, clcolor, clcolor);
    circle(0.15f, 0.3f, 0.0f, clcolor, clcolor, clcolor);
    glPopMatrix();
}

void smoke() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(-0.1f, 1.15f, 0.0f);
    glScalef(smokescal, smokescal, 1.0f);

    circleAlpha(0.12f, 0.0f, 0.0f, 0.4f, 0.4f, 0.4f, 0.7f);
    circleAlpha(0.15f, 0.05f, 0.15f, 0.5f, 0.5f, 0.5f, 0.5f);
    circleAlpha(0.18f, -0.02f, 0.35f, 0.6f, 0.6f, 0.6f, 0.3f);

    glPopMatrix();
    glDisable(GL_BLEND);
}

void drawBomb() {
    if (bombfall) {
        glPushMatrix();
        glTranslatef(bombX, bombY, 0.0f);
        glScalef(0.6f, 0.6f, 1.0f);
        glColor3f(0.3f, 0.35f, 0.2f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.1f);
        glVertex2f(0.08f, 0.1f);
        glVertex2f(0.06f, -0.15f);
        glVertex2f(-0.06f, -0.15f);
        glEnd();

        glColor3f(0.6f, 0.1f, 0.1f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.06f, -0.15f);
        glVertex2f(0.06f, -0.15f);
        glVertex2f(0.0f, -0.25f);
        glEnd();

        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.08f, 0.1f);
        glVertex2f(-0.08f, 0.2f);
        glVertex2f(-0.15f, 0.25f);
        glVertex2f(0.08f, 0.1f);
        glVertex2f(0.08f, 0.2f);
        glVertex2f(0.15f, 0.25f);
        glEnd();
        glPopMatrix();
    }
}

void drawFlash() {
    if (flashh) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
        glBegin(GL_QUADS);
        glVertex2f(-2.0f, -2.0f);
        glVertex2f( 2.0f, -2.0f);
        glVertex2f( 2.0f,  2.0f);
        glVertex2f(-2.0f,  2.0f);
        glEnd();
        glDisable(GL_BLEND);
    }
}

void drawSun() {
    circle(0.15f, -1.2f, sunY, 1.0f, 0.9f, 0.0f);
}

void drawMoon() {
    circle(0.12f, -0.9f, moonY, 0.9f, 0.9f, 0.9f);
    circle(0.03f, -0.87f, moonY + 0.03f, 0.8f, 0.8f, 0.8f);
}

void drawLightBeams() {
    if (!s_light) return;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(lightopa > 0.01f) {
        glColor4f(1.0f, 1.0f, 0.8f, lightopa);
        glBegin(GL_TRIANGLES);
        glVertex2f(-1.735f, 1.1f);
        glVertex2f(-1.95f, 0.4f);
        glVertex2f(-1.52f, 0.4f);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(0.26f, 1.1f);
        glVertex2f(0.05f, 0.4f);
        glVertex2f(0.47f, 0.4f);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(1.26f, 1.1f);
        glVertex2f(1.05f, 0.4f);
        glVertex2f(1.47f, 0.4f);
        glEnd();
    }
    if (!isDay && lightopa > 0.1f) {
        glPushMatrix();
        glTranslatef(1.85f, 1.18f, 0.0f);
        glRotatef(lightangle, 0.0f, 0.0f, 1.0f);
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 1.0f, 0.25f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.35f, 3.0f);
        glVertex2f(0.35f, 3.0f);
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}


void water() {
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.7f, 1.0f);
    glVertex2f(-4.0f, -0.8f);
    glVertex2f( 4.0f, -0.8f);
    glColor3f(0.0f, 0.4f, 0.8f);
    glVertex2f( 4.0f, -2.0f);
    glVertex2f(-4.0f, -2.0f);
    glEnd();
}

void roadLines() {
    layer(-4.0f, -0.22f, -3.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(-3.0f, -0.22f, -2.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(-2.0f, -0.22f, -1.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(-1.0f, -0.22f, -0.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(0.0f, -0.22f, 0.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(1.0f, -0.22f, 1.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(2.0f, -0.22f, 2.5f, -0.18f, 1.0f, 1.0f, 0.0f);
    layer(3.0f, -0.22f, 3.5f, -0.18f, 1.0f, 1.0f, 0.0f);
}

void road() {
    layer(-4.0f, 0.38f, 4.0f, 0.42f, 0.2f, 0.2f, 0.2f);
    layer(-4.0f, -0.82f, 4.0f, -0.78f, 0.2f, 0.2f, 0.2f);
}

void divider() {
    layer(-4.0f, -0.60f, 4.0f, -0.58f, 0.3f, 0.3f, 0.3f);
    layer(-4.0f, -0.68f, 4.0f, -0.66f, 0.3f, 0.3f, 0.3f);

    layer(-4.0f, -0.8f, -3.95f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-3.5f, -0.8f, -3.45f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-3.0f, -0.8f, -2.95f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-2.5f, -0.8f, -2.45f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-2.0f, -0.8f, -1.95f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-1.5f, -0.8f, -1.45f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-1.0f, -0.8f, -0.95f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(-0.5f, -0.8f, -0.45f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(0.0f, -0.8f, 0.05f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(0.5f, -0.8f, 0.55f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(1.0f, -0.8f, 1.05f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(1.5f, -0.8f, 1.55f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(2.0f, -0.8f, 2.05f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(2.5f, -0.8f, 2.55f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(3.0f, -0.8f, 3.05f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(3.5f, -0.8f, 3.55f, -0.55f, 0.2f, 0.2f, 0.2f);
    layer(4.0f, -0.8f, 4.05f, -0.55f, 0.2f, 0.2f, 0.2f);
}

void building1() {
    layer(-1.9f, 0.4f, -1.3f, 1.4f, 0.45f, 0.25f, 0.20f);
    layer(-1.8f, 1.1f, -1.7f, 1.2f, 0.9f, 0.8f, 0.4f);
    layer(-1.5f, 1.1f, -1.4f, 1.2f, 0.9f, 0.8f, 0.4f);
    layer(-1.8f, 0.7f, -1.7f, 0.8f, 0.9f, 0.8f, 0.4f);
}

void building2() {
    layer(0.9f, 0.4f, 1.4f, 1.2f, 0.20f, 0.25f, 0.30f);
    layer(1.0f, 0.9f, 1.15f, 1.0f, 0.6f, 0.7f, 0.8f);
    layer(1.0f, 0.6f, 1.15f, 0.7f, 0.6f, 0.7f, 0.8f);
}

void building3() {
    layer(1.4f, 0.4f, 1.9f, 1.5f, 0.60f, 0.55f, 0.45f);
    layer(1.5f, 1.3f, 1.6f, 1.4f, 0.8f, 0.7f, 0.3f);
}

void building4() {
    layer(-0.6f, 0.4f, -0.2f, 1.3f, 0.55f, 0.55f, 0.6f);
    layer(0.2f, 0.4f, 0.6f, 1.1f, 0.50f, 0.50f, 0.55f);
    layer(-0.2f, 0.4f, 0.2f, 1.0f, 0.15f, 0.15f, 0.15f);
    layer(-0.6f, 1.3f, -0.35f, 1.4f, 0.4f, 0.4f, 0.45f);
    layer(0.35f, 1.1f, 0.6f, 1.2f, 0.4f, 0.4f, 0.45f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, 0.8f);
    glVertex2f(0.15f, 0.8f);
    glVertex2f(0.10f, 0.75f);
    glVertex2f(-0.10f, 0.75f);
    glEnd();
    layer(-0.5f, 0.55f, -0.35f, 0.7f, 0.1f, 0.1f, 0.1f);
    layer(-0.5f, 0.85f, -0.35f, 1.0f, 0.1f, 0.1f, 0.1f);
    layer(0.35f, 0.6f, 0.5f, 0.75f, 0.1f, 0.1f, .1f);
    layer(0.35f, 0.85f, 0.5f, 1.0f, 0.1f, 0.1f, 0.1f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(-0.25f, 1.3f);
    glVertex2f(-0.35f, 0.6f);
    glVertex2f(0.25f, 1.1f);
    glVertex2f(0.35f, 0.5f);
    glEnd();
    glColor3f(0.35f, 0.35f, 0.35f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.15f, 0.4f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(-0.08f, 0.48f);
    glVertex2f(0.05f, 0.4f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.12f, 0.47f);
    glEnd();
}

void searchlight() {
    layer(1.75f, 0.4f, 1.95f, 0.55f, 0.25f, 0.25f, 0.25f);
    layer(1.83f, 0.55f, 1.87f, 1.05f, 0.35f, 0.35f, 0.35f);
    layer(1.80f, 0.75f, 1.90f, 0.78f, 0.25f, 0.25f, 0.25f);
    layer(1.80f, 0.95f, 1.90f, 0.98f, 0.25f, 0.25f, 0.25f);
    layer(1.78f, 1.05f, 1.92f, 1.12f, 0.20f, 0.20f, 0.20f);
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
    glVertex2f(1.92f, 1.22f);
    glVertex2f(1.82f, 1.25f);
    glVertex2f(1.82f, 1.11f);
    glVertex2f(1.92f, 1.14f);
    glEnd();
    circle(0.035f, 1.85f, 1.18f, 1.0f, 0.9f, 0.6f);
}

void streetlights() {
    layer(-1.6f, 0.4f, -1.58f, 1.1f, 0.3f, 0.3f, 0.3f);
    layer(-1.75f, 1.1f, -1.58f, 1.12f, 0.3f, 0.3f, 0.3f);
    layer(-1.75f, 1.05f, -1.72f, 1.1f, 0.9f, 0.9f, 0.9f);
    layer(0.4f, 0.4f, 0.42f, 1.1f, 0.3f, 0.3f, 0.3f);
    layer(0.25f, 1.1f, 0.42f, 1.12f, 0.3f, 0.3f, 0.3f);
    layer(0.25f, 1.05f, 0.27f, 1.1f, 0.9f, 0.9f, 0.9f);
    layer(1.4f, 0.4f, 1.42f, 1.1f, 0.3f, 0.3f, 0.3f);
    layer(1.25f, 1.1f, 1.42f, 1.12f, 0.3f, 0.3f, 0.3f);
    layer(1.25f, 1.05f, 1.27f, 1.1f, 0.9f, 0.9f, 0.9f);
}

void car1() {
    layer(-0.6f, -0.55f, 0.6f, -0.4f, 0.15f, 0.15f, 0.15f);
    glBegin(GL_POLYGON);
    glColor3f(0.25f, 0.3f, 0.25f);
    glVertex2f(-0.55f, -0.4f);
    glVertex2f(0.55f, -0.4f);
    glVertex2f(0.45f, -0.1f);
    glVertex2f(-0.45f, -0.1f);
    glEnd();
    layer(-0.4f, -0.3f, -0.1f, -0.2f, 0.2f, 0.25f, 0.2f);
    layer(0.1f, -0.3f, 0.4f, -0.2f, 0.2f, 0.25f, 0.2f);
    layer(-0.25f, -0.1f, 0.2f, 0.1f, 0.3f, 0.35f, 0.3f);
    layer(0.2f, -0.02f, 0.65f, 0.05f, 0.1f, 0.1f, 0.1f);
    layer(0.6f, -0.04f, 0.7f, 0.07f, 0.2f, 0.2f, 0.2f);
    layer(0.25f, -0.15f, 0.35f, -0.12f, 0.0f, 0.0f, 0.0f);
    float ax = -0.5f;
    circle(0.12f, -0.4f, ax, 0.05f, 0.05f, 0.05f);
    circle(0.05f, -0.4f, ax, 0.4f, 0.4f, 0.4f);
    circle(0.12f, -0.13f, ax, 0.05f, 0.05f, 0.05f);
    circle(0.05f, -0.13f, ax, 0.4f, 0.4f, 0.4f);
    circle(0.12f, 0.13f, ax, 0.05f, 0.05f, 0.05f);
    circle(0.05f, 0.13f, ax, 0.4f, 0.4f, 0.4f);
    circle(0.12f, 0.4f, ax, 0.05f, 0.05f, 0.05f);
    circle(0.05f, 0.4f, ax, 0.4f, 0.4f, 0.4f);
}

void Warship() {
    glColor3f(0.1f, 0.1f, 0.15f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7f, -1.6f);
    glVertex2f(0.6f, -1.6f);
    glVertex2f(0.8f, -1.45f);
    glVertex2f(-0.8f, -1.45f);
    glEnd();
    glColor3f(0.3f, 0.35f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.8f, -1.45f);
    glVertex2f(0.8f, -1.45f);
    glVertex2f(0.75f, -1.35f);
    glVertex2f(-0.85f, -1.35f);
    glEnd();
    layer(-0.4f, -1.35f, 0.2f, -1.25f, 0.4f, 0.45f, 0.5f);
    layer(-0.3f, -1.25f, 0.0f, -1.15f, 0.45f, 0.5f, 0.55f);
    layer(-0.28f, -1.20f, -0.02f, -1.17f, 0.0f, 0.8f, 1.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0.05f, -1.25f);
    glVertex2f(0.15f, -1.25f);
    glVertex2f(0.12f, -1.10f);
    glVertex2f(0.08f, -1.10f);
    glEnd();
    layer(-0.15f, -1.15f, -0.12f, -0.95f, 0.2f, 0.2f, 0.2f);
    layer(-0.25f, -1.05f, -0.02f, -1.02f, 0.2f, 0.2f, 0.2f);
    circle(0.03f, -0.135f, -0.95f, 0.1f, 0.1f, 0.1f);
    layer(0.4f, -1.35f, 0.55f, -1.30f, 0.3f, 0.3f, 0.3f);
    layer(0.50f, -1.33f, 0.70f, -1.31f, 0.1f, 0.1f, 0.1f);
    layer(-0.6f, -1.35f, -0.5f, -1.28f, 0.25f, 0.25f, 0.25f);
    layer(-0.80f, -1.35f, -0.79f, -1.20f, 0.1f, 0.1f, 0.1f);
    glColor3f(0.9f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.79f, -1.20f);
    glVertex2f(-0.65f, -1.25f);
    glVertex2f(-0.79f, -1.30f);
    glEnd();
}

void jet() {
    glColor3f(0.6f, 0.6f, 0.65f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 1.8f);
    glVertex2f(0.3f, 1.8f);
    glVertex2f(0.5f, 1.75f);
    glVertex2f(0.3f, 1.7f);
    glVertex2f(-0.3f, 1.7f);
    glEnd();
    glColor3f(0.4f, 0.7f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 1.8f);
    glVertex2f(0.15f, 1.8f);
    glVertex2f(0.05f, 1.88f);
    glVertex2f(-0.1f, 1.86f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.1f, 1.75f);
    glVertex2f(0.1f, 1.75f);
    glVertex2f(-0.2f, 1.5f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.35f, 1.8f);
    glVertex2f(-0.15f, 1.8f);
    glVertex2f(-0.30f, 2.05f);
    glEnd();
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.4f, 1.78f);
    glVertex2f(-0.4f, 1.72f);
    glVertex2f(-0.55f, 1.75f);
    glEnd();
    layer(-0.1f, 1.65f, 0.05f, 1.68f, 0.8f, 0.8f, 0.8f);
    layer(-0.1f, 1.65f, -0.08f, 1.63f, 0.3f, 0.3f, 0.3f);
    layer(0.05f, 1.65f, 0.07f, 1.68f, 0.9f, 0.0f, 0.0f);
    layer(0.0f, 1.65f, 0.15f, 1.68f, 0.8f, 0.8f, 0.8f);
    layer(0.0f, 1.65f, 0.02f, 1.63f, 0.3f, 0.3f, 0.3f);
    layer(0.15f, 1.65f, 0.17f, 1.68f, 0.9f, 0.0f, 0.0f);
    circle(0.005f, -0.30f, 1.75f, 0.3f, 0.3f, 0.3f);
    circle(0.005f, -0.22f, 1.75f, 0.3f, 0.3f, 0.3f);
    circle(0.005f, -0.14f, 1.75f, 0.3f, 0.3f, 0.3f);
    circle(0.005f, -0.06f, 1.75f, 0.3f, 0.3f, 0.3f);
    circle(0.005f, 0.02f, 1.75f, 0.3f, 0.3f, 0.3f);
    circle(0.005f, 0.10f, 1.75f, 0.3f, 0.3f, 0.3f);
    circle(0.005f, 0.18f, 1.75f, 0.3f, 0.3f, 0.3f);
}

void fire() {
    glColor3f(1.0f, 0.3f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.20f, 0.45f);
    glVertex2f(0.10f, 0.45f);
    glVertex2f(-0.05f, 0.98f);
    glEnd();

    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.16f, 0.53f);
    glVertex2f(0.06f, 0.53f);
    glVertex2f(-0.05f, 0.87f);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.11f, 0.57f);
    glVertex2f(0.01f, 0.57f);
    glVertex2f(-0.05f, 0.75f);
    glEnd();

    glColor3f(1.0f, 0.3f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.03f, 0.65f);
    glVertex2f(0.27f, 0.65f);
    glVertex2f(0.15f, 1.07f);
    glEnd();

    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.07f, 0.71f);
    glVertex2f(0.23f, 0.71f);
    glVertex2f(0.15f, 0.99f);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.10f, 0.75f);
    glVertex2f(0.20f, 0.75f);
    glVertex2f(0.15f, 0.89f);
    glEnd();

    glColor3f(1.0f, 0.3f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.30f, 0.85f);
    glVertex2f(-0.10f, 0.85f);
    glVertex2f(-0.20f, 1.20f);
    glEnd();

    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.27f, 0.90f);
    glVertex2f(-0.13f, 0.90f);
    glVertex2f(-0.20f, 1.13f);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.24f, 0.93f);
    glVertex2f(-0.16f, 0.93f);
    glVertex2f(-0.20f, 1.05f);
    glEnd();
}

void update(int value) {

    if (jettimer > 0) jettimer--;
    else jetc = jetbase;

    jetmov += jetc;
    if(jetmov > 4.5f) jetmov = -4.5f;

    if(carmoving) {
        carmov += 0.01f;
        if(carmov > 4.0f) carmov = -4.0f;
    }

    if(shipmoving) {
        shipmov += 0.005f;
        if(shipmov > 4.0f) shipmov = -4.0f;
    }

    smokescal += 0.01f;
    if(smokescal > 1.3f) smokescal = 1.0f;

    clx1 += 0.002f;
    clx2 += 0.003f;
    if(clx1 > 2.5f) clx1 = -2.5f;
    if(clx2 > 2.5f) clx2 = -2.5f;

    if (flashh) {
        flashtimer--;
        if (flashtimer <= 0) flashh = false;
    }
    if(!isDay) {
        lightangle += 0.5f * lightDir;
        if (lightangle > 45.0f || lightangle < -45.0f) lightDir *= -1.0f;
    }
    if (bombfall) {
        bombY -= 0.05f;
        if (bombY < 0.8f) {
            bombfall = false;
            explode = true;
            exploscale = 0.1f;
            flashh = true;
            flashtimer = 5;
        }
    }
    if (explode) {
        exploscale += 0.05f;
        if (exploscale > 1.5f) {
            explode = false;
            exploscale = 0.0f;
        }
    }
    if(isDay) {
        if(skyr > 0.05f) skyr -= 0.003f;
        if(skyg > 0.05f) skyg -= 0.003f;
        if(skyb > 0.2f) skyb -= 0.003f;
        sunY -= 0.01f;
        if(moonY < 1.6f) moonY += 0.01f;
        if(moonY > -1.0f && lightopa < 0.6f) lightopa += 0.005f;
        if(moonY >= 1.6f) isDay = false;
    }
    else {
        if(skyr < 0.5f) skyr += 0.0005f;
        if(skyg < 0.8f) skyg += 0.0005f;
        if(skyb < 1.0f) skyb += 0.0005f;
        if(sunY < 1.6f) sunY += 0.002f;
        moonY -= 0.002f;
        if(sunY > -1.0f && lightopa > 0.0f) lightopa -= 0.001f;
        if(sunY >= 1.6f) isDay = true;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}


void mouseClick(int button, int state, int x, int y) {

        if (button == GLUT_LEFT_BUTTON) {
            if (!bombfall && !explode) {
                bombX = jetmov;
                bombY = 1.75f;
                bombfall = true;
            }
        }

        else if (button == GLUT_RIGHT_BUTTON) {
            jetc = 0.08f;
            jettimer = 50;
        }

}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'e': case 'E':
            flashh = true;
            flashtimer = 5;
            break;
        case 'l': case 'L':
            s_light = !s_light;
            break;
        case 'w': case 'W':
            shipmoving = !shipmoving;
            break;
        case 'c': case 'C':
            carmoving = !carmoving;
            break;

        case 'n': case 'N':
            isDay = !isDay;
            if(isDay) {
                sunY = 1.6f;
                moonY = -1.6f;
                skyr = 0.5f;
                skyg = 0.8f;
                skyb = 1.0f;
                lightopa = 0.0f;
            } else {
                sunY = -1.6f;
                moonY = 1.6f;
                skyr = 0.05f;
                skyg = 0.05f;
                skyb = 0.2f;
                lightopa = 0.6f;
            }
            break;
    }
}

void display() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    layer(-4.0f,  0.4f, 4.0f,  2.0f,skyr,skyg,skyb);

    drawStars();
    drawSun();
    drawMoon();
    drawClouds();

    layer(-4.0f,  0.4f, 4.0f,  0.55f,   0.2f, 0.5f, 0.2f);
    layer(-4.0f, -0.8f, 4.0f,  0.4f,    0.6f, 0.6f, 0.6f);

    water();
    roadLines();
    road();
    divider();

    building1();
    building4();
    building2();
    building3();

    smoke();
    streetlights();
    searchlight();
    fire();

    glPushMatrix();
    glTranslatef(jetmov, 0.0f, 0.0f);
    jet();
    glPopMatrix();

    drawBomb();
    drawExplosion();

    glPushMatrix();
    glTranslatef(carmov, 0.0f, 0.0f);
    car1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(shipmov, 0.0f, 0.0f);
    Warship();
    glPopMatrix();

    drawLightBeams();
    drawFlash();

    text();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("War Scenario");
    gluOrtho2D(-2, 2, -2, 2);

    glutDisplayFunc(display);
    glutTimerFunc(20, update, 0);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
