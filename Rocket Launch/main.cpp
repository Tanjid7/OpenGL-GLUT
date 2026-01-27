#include <windows.h>  // Added for MS Windows compatibility
#include <GL/glut.h>
#include <math.h>
#include <string.h>

// --- Global Variables ---
float heliMove = -1.2f;
float currentHeliSpeed = 0.009f; // Default Helicopter Speed

float ship1Move = -0.7f;
float ship2Move = 0.4f;
float rocketMove = 0.0f;

// Cloud Variables
float cloud1Move = -0.8f;
float cloud2Move = 0.6f;

// UFO Variable
float ufoMove = 1.2f; // Starts off-screen to the right

// Control State Variables
bool isLaunched = false;    // Controls if rocket is flying
bool isDay = true;          // Controls Day/Night background
bool shipsMoving = true;    // Controls if ships are moving (Key 'e')


// --- NEW: Text Rendering Function (As requested) ---
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);  // Set the position to start drawing text
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Render each character
    }
}

// --- Helper: Draw Circle (Solid) ---
void circle(float radius, float xc, float yc, float r, float g, float b) {
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++) {
        glColor3f(r, g, b);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float rad = radius;
        float x = rad * cos(A);
        float y = rad * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

// --- Helper Draw Circle with Alpha (Transparency) ---
void drawAlphaCircle(float radius, float xc, float yc, float r, float g, float b, float a) {
    glBegin(GL_POLYGON);
    for(int i=0; i<200; i++) {
        glColor4f(r, g, b, a); // 'a' controls transparency
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float rad = radius;
        float x = rad * cos(A);
        float y = rad * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

// --- Draw Cloud Function ---
void drawCloud(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);

    float cR = isDay ? 1.0f : 0.5f;
    float cG = isDay ? 1.0f : 0.5f;
    float cB = isDay ? 1.0f : 0.6f;

    circle(0.1f, 0.0f, 0.0f, cR, cG, cB);
    circle(0.08f, -0.12f, -0.02f, cR, cG, cB);
    circle(0.08f, 0.12f, -0.02f, cR, cG, cB);
    circle(0.06f, 0.05f, 0.08f, cR, cG, cB);

    glPopMatrix();
}

// --- Draw UFO Function ---
void drawUFO(float x, float y) {
    if(isDay) return;

    glPushMatrix();
    glTranslatef(x, y, 0);

    // Green Alien Dome
    circle(0.04f, 0.0f, 0.05f, 0.0f, 1.0f, 0.0f);

    // Saucer body (Purple)
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.0f, 0.5f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.05f, -0.05f);
    glVertex2f(-0.05f, -0.05f);
    glEnd();

    // Blinking Lights
    circle(0.01f, -0.08f, -0.02f, 1.0f, 0.0f, 0.0f);
    circle(0.01f, 0.0f, -0.02f, 1.0f, 1.0f, 0.0f);
    circle(0.01f, 0.08f, -0.02f, 1.0f, 0.0f, 0.0f);

    glPopMatrix();
}

// --- Draw Ship ---
void drawShip(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);

    // Ship Body
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, -0.05f); glVertex2f(0.2f, -0.05f);
        glVertex2f(0.18f, -0.1f);  glVertex2f(-0.18f, -0.1f);
    glEnd();

    // Deck
    glColor3f(0.3f, 0.3f, 0.3f);
    glRectf(-0.2f, 0.0f, 0.2f, -0.05f);

    // Cabin structures
    glColor3f(0.9f, 0.9f, 0.9f);
    glRectf(-0.05f, 0.0f, 0.08f, 0.08f);
    glRectf(0.08f, 0.0f, 0.15f, 0.04f);

    // Windows
    glColor3f(0.1f, 0.3f, 0.5f);
    glRectf(-0.03f, 0.05f, -0.01f, 0.07f);
    glRectf(0.01f, 0.05f, 0.03f, 0.07f);
    glRectf(0.05f, 0.05f, 0.07f, 0.07f);

    // Night Lights
    if(!isDay) {
        circle(0.03f, 0.0f, 0.04f, 1.0f, 0.9f, 0.2f);
        circle(0.015f, 0.19f, -0.05f, 1.0f, 0.0f, 0.0f);
        circle(0.015f, -0.19f, -0.05f, 0.0f, 1.0f, 0.0f);
    }

    // Mast and flags
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(-0.12f, 0.0f); glVertex2f(-0.12f, 0.12f);
        glVertex2f(0.02f, 0.08f); glVertex2f(0.02f, 0.15f);
    glEnd();

    glColor3f(0.6f, 0.1f, 0.1f);
    glRectf(-0.02f, 0.08f, 0.01f, 0.12f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glRectf(-0.02f, 0.12f, 0.01f, 0.13f);
    glPopMatrix();
}

// --- Draw Background ---
void drawBackground() {
    glBegin(GL_QUADS);
        if(isDay) {
            glColor3f(0.2f, 0.5f, 0.9f);
            glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
            glColor3f(0.6f, 0.8f, 1.0f);
            glVertex2f(1.0f, -0.3f); glVertex2f(-1.0f, -0.3f);
        } else {
            glColor3f(0.05f, 0.05f, 0.2f);
            glVertex2f(-1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
            glColor3f(0.1f, 0.1f, 0.35f);
            glVertex2f(1.0f, -0.3f); glVertex2f(-1.0f, -0.3f);
        }
    glEnd();

    // Stars
    if(!isDay) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
            glVertex2f(-0.8f, 0.8f); glVertex2f(-0.6f, 0.9f);
            glVertex2f(-0.9f, 0.5f); glVertex2f(-0.3f, 0.7f);
            glVertex2f(0.0f, 0.95f); glVertex2f(0.2f, 0.6f);
            glVertex2f(0.5f, 0.85f); glVertex2f(0.8f, 0.7f);
            glVertex2f(0.9f, 0.4f);  glVertex2f(0.3f, 0.3f);
            glVertex2f(-0.5f, 0.2f); glVertex2f(-0.1f, 0.4f);
            glVertex2f(0.6f, 0.1f);  glVertex2f(-0.7f, 0.0f);
        glEnd();
    }

    // Ocean
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.3f, 0.5f);
        glVertex2f(-1.0f, -0.3f); glVertex2f(1.0f, -0.3f);
        glColor3f(0.1f, 0.6f, 0.8f);
        glVertex2f(1.0f, -1.0f); glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Horizon lines
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.8f, -0.4f); glVertex2f(-0.6f, -0.4f);
        glVertex2f(0.2f, -0.45f);  glVertex2f(0.5f, -0.45f);
        glVertex2f(-0.4f, -0.6f);  glVertex2f(-0.1f, -0.6f);
        glVertex2f(0.6f, -0.7f);   glVertex2f(0.9f, -0.7f);
    glEnd();

    // Sun or Moon
    if(isDay) {
        circle(0.12f, 0.7f, 0.8f, 1.0f, 0.9f, 0.0f);
        circle(0.14f, 0.7f, 0.8f, 1.0f, 0.8f, 0.2f);
    } else {
        circle(0.10f, 0.7f, 0.8f, 0.9f, 0.9f, 0.9f);
        circle(0.08f, 0.73f, 0.83f, 0.05f, 0.05f, 0.2f);
    }
}

// --- Draw Helicopter ---
void drawHelicopter(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // Heli Body
    glBegin(GL_POLYGON);
        glColor3f(0.15f, 0.3f, 0.15f);
        glVertex2f(-0.1f, -0.05f); glVertex2f(0.1f, -0.05f);
        glVertex2f(0.14f, 0.02f);  glVertex2f(0.08f, 0.09f);
        glVertex2f(-0.08f, 0.09f); glVertex2f(-0.12f, 0.02f);
    glEnd();

    // Cockpit Window
    glColor3f(0.3f, 0.5f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(0.04f, 0.01f); glVertex2f(0.12f, 0.02f);
        glVertex2f(0.08f, 0.08f); glVertex2f(0.04f, 0.08f);
    glEnd();

    // Rotor & Tail
    circle(0.015f, 0.06f, 0.06f, 0.6f, 0.8f, 1.0f);

    glColor3f(0.12f, 0.25f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 0.02f); glVertex2f(-0.1f, 0.02f);
        glVertex2f(-0.1f, 0.05f); glVertex2f(-0.3f, 0.06f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.2f, 0.1f);
        glVertex2f(-0.3f, 0.04f); glVertex2f(-0.35f, 0.12f); glVertex2f(-0.25f, 0.04f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-0.33f, 0.04f, -0.32f, 0.12f);
    glRectf(-0.36f, 0.07f, -0.29f, 0.08f);

    glColor3f(0.2f, 0.2f, 0.2f);
    glRectf(-0.015f, 0.09f, 0.015f, 0.13f);
    circle(0.02f, 0.0f, 0.13f, 0.1f, 0.1f, 0.1f);
    glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, 0.13f); glVertex2f(0.35f, 0.13f);
        glVertex2f(0.35f, 0.14f); glVertex2f(-0.35f, 0.14f);
    glEnd();

    // Night Lights
    if(!isDay) {
        circle(0.025f, 0.14f, 0.0f, 1.0f, 1.0f, 0.8f);
        circle(0.015f, -0.35f, 0.12f, 1.0f, 0.0f, 0.0f);
    }

    // Skids
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(3.0);
    glBegin(GL_LINES);
        glVertex2f(-0.05f, -0.05f); glVertex2f(-0.07f, -0.11f);
        glVertex2f(0.05f, -0.05f);  glVertex2f(0.07f, -0.11f);
        glVertex2f(-0.15f, -0.11f); glVertex2f(0.15f, -0.11f);
    glEnd();
    glPopMatrix();
}

// --- Draw Launch Tower & Pad ---
void drawLaunchTower() {
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(0.35f, -0.8f); glVertex2f(0.35f, 0.6f);
    glVertex2f(0.55f, -0.8f); glVertex2f(0.55f, 0.6f);
    glVertex2f(0.35f, 0.0f);  glVertex2f(0.55f, 0.0f);
    glVertex2f(0.35f, 0.3f);  glVertex2f(0.55f, 0.3f);
    glEnd();
}

void drawLaunchPad() {
    glColor3f(0.25f, 0.25f, 0.25f);
    glRectf(-0.9f, -1.0f, 0.9f, -0.82f);
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, -0.82f); glVertex2f(0.25f, -0.82f);
        glVertex2f(0.3f, -0.78f);   glVertex2f(-0.3f, -0.78f);
    glEnd();
    glColor3f(0.8f, 0.7f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.7f, -0.82f); glVertex2f(-0.55f, -0.82f);
        glVertex2f(-0.6f, -0.86f); glVertex2f(-0.75f, -0.86f);
        glVertex2f(0.55f, -0.82f); glVertex2f(0.7f, -0.82f);
        glVertex2f(0.65f, -0.86f); glVertex2f(0.5f, -0.86f);
    glEnd();
}

// --- Draw Smoke ---
void drawSmoke() {
    if(rocketMove > 0.01f) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // --- Layer 1: Top ---
        drawAlphaCircle(0.08f, 0.0f, -1.0f, 0.9f, 0.9f, 0.9f, 0.9f);

        // --- Layer 2: Middle ---
        drawAlphaCircle(0.12f, -0.06f, -1.15f, 0.8f, 0.8f, 0.8f, 0.7f);
        drawAlphaCircle(0.12f, 0.06f, -1.15f, 0.8f, 0.8f, 0.8f, 0.7f);

        // --- Layer 3: Bottom ---
        drawAlphaCircle(0.16f, 0.0f, -1.35f, 0.6f, 0.6f, 0.6f, 0.5f);
        drawAlphaCircle(0.15f, -0.12f, -1.3f, 0.6f, 0.6f, 0.6f, 0.5f);
        drawAlphaCircle(0.15f, 0.12f, -1.3f, 0.6f, 0.6f, 0.6f, 0.5f);

        glDisable(GL_BLEND);
    }
}

// --- Draw Rocket ---
void drawRocket() {
    glBegin(GL_QUADS);
        glColor3f(0.7f, 0.7f, 0.7f); glVertex2f(-0.08f, -0.78f);
        glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.08f, -0.78f);
        glColor3f(1.0f, 1.0f, 1.0f); glVertex2f(0.08f, 0.2f);
        glColor3f(0.7f, 0.7f, 0.7f); glVertex2f(-0.08f, 0.2f);
    glEnd();
    glColor3f(0.85f, 0.85f, 0.85f);
    glRectf(-0.14f, -0.78f, -0.08f, -0.1f);
    glRectf(0.08f, -0.78f, 0.14f, -0.1f);
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.08f, 0.2f); glVertex2f(0.08f, 0.2f); glVertex2f(0.0f, 0.5f);
    glEnd();
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.14f, -0.78f); glVertex2f(-0.35f, -0.88f); glVertex2f(-0.14f, -0.3f);
        glVertex2f(0.14f, -0.78f);  glVertex2f(0.35f, -0.88f);  glVertex2f(0.14f, -0.3f);
    glEnd();
    circle(0.035f, 0.0f, 0.25f, 0.1f, 0.3f, 0.6f);
    circle(0.01f, -0.01f, 0.26f, 1.0f, 1.0f, 1.0f);
}

void drawRocketFire() {
    if(rocketMove > 0.01f) {
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex2f(-0.08f, -0.78f);
            glVertex2f(0.08f, -0.78f);
            glVertex2f(0.0f, -0.95f);
            glColor3f(1.0f, 0.8f, 0.0f);
            glVertex2f(-0.04f, -0.78f);
            glVertex2f(0.04f, -0.78f);
            glVertex2f(0.0f, -0.88f);
        glEnd();
    }
}

// --- INPUT: Keyboard ---
void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Rocket Launch
        case 'W':
            isLaunched = true;
            break;
        case 'e': // Ship Stop (Toggle)
        case 'E':
            shipsMoving = !shipsMoving;
            break;
        case 's': // Night and Day Change
        case 'S':
            isDay = !isDay;
            break;
        case 'd': // Reset the Scene
        case 'D':
            isLaunched = false;
            rocketMove = 0.0f;
            heliMove = -1.2f;
            ship1Move = -0.7f;
            ship2Move = 0.4f;
            currentHeliSpeed = 0.009f;
            shipsMoving = true;
            ufoMove = 1.2f; // Reset UFO
            break;
    }
    glutPostRedisplay();
}

// --- INPUT: Mouse ---
void handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) currentHeliSpeed = 0.03f; // Fast
        else if (button == GLUT_RIGHT_BUTTON) currentHeliSpeed = 0.002f; // Slow
    }
    else if (state == GLUT_UP) {
        currentHeliSpeed = 0.009f; // Normal
    }
}

// --- Update Function ---
void update(int value) {
    // 1. Helicopter Move
    heliMove += currentHeliSpeed;
    if(heliMove > 1.2f) heliMove = -1.2f;

    // 2. Ship Move
    if (shipsMoving) {
        ship1Move += 0.002f;
        if(ship1Move > 1.2f) ship1Move = -1.2f;
        ship2Move -= 0.003f;
        if(ship2Move < -1.2f) ship2Move = 1.2f;
    }

    // 3. Rocket Move
    if(isLaunched) rocketMove += 0.017f;

    // 4. Cloud Move
    cloud1Move += 0.001f;
    if(cloud1Move > 1.2f) cloud1Move = -1.2f;
    cloud2Move += 0.0015f;
    if(cloud2Move > 1.2f) cloud2Move = -1.2f;

    // 5. UFO Move
    if(!isDay) {
        ufoMove -= 0.015f;
        if(ufoMove < -1.2f) ufoMove = 1.2f;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

// --- Display Function ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawUFO(ufoMove, 0.85f);
    drawCloud(cloud1Move, 0.8f, 0.6f);
    drawCloud(cloud2Move, 0.65f, 0.8f);
    drawShip(ship1Move, -0.35f, 0.5f);
    drawShip(ship2Move, -0.5f, 0.7f);
    drawHelicopter(heliMove, 0.65);
    drawLaunchPad();
    drawLaunchTower();

    glPushMatrix();
    glTranslatef(0.0f, rocketMove, 0.0f);
    drawRocket();
    drawRocketFire();
    drawSmoke();
    glPopMatrix();

    // --- HUD (Implemented using renderText) ---
    glColor3f(1.0f, 1.0f, 1.0f);

    if(isLaunched) {
        renderText(-0.9f, 0.9f, "STATUS: LAUNCH IN PROGRESS");
    } else {
        renderText(-0.9f, 0.9f, "STATUS: READY (Press 'W' to Launch)");
    }

    if(currentHeliSpeed > 0.02f) renderText(0.6f, 0.9f, "HELI: TURBO");
    else if(currentHeliSpeed < 0.005f) renderText(0.6f, 0.9f, "HELI: SLOW");
    else renderText(0.6f, 0.9f, "HELI: NORMAL");

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rocket Scenario");

    glutDisplayFunc(display);
    glutTimerFunc(20, update, 0);
    glutKeyboardFunc(handleKeyboard);
    glutMouseFunc(handleMouse);

    glutMainLoop();
    return 0;
}
