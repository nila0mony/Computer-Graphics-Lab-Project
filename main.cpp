#include <GL/glut.h>
#include <cmath>


// --- Global states ---
bool boatMoving = false;
bool birdsMoving = false;
float boatOffset = 0.0f;
float birdOffset = 0.0f;
float brightness = 1.0f;
float starBrightness = 1.0f;
bool starDim = true;

int timeOfDay = 0; // 0=Morning, 1=Afternoon, 2=Midday, 3=Night

void updateBrightness() {
    if (timeOfDay == 0) {
        brightness = 0.8f;
    } else if (timeOfDay == 1) {
        brightness = 0.9f;
    } else if (timeOfDay == 2) {
        brightness = 1.0f;
    } else if (timeOfDay == 3) {
        brightness = 0.65f;
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'm') timeOfDay = 0;
    if (key == 'a') timeOfDay = 1;
    if (key == 'd') timeOfDay = 2;
    if (key == 'n') timeOfDay = 3;
    updateBrightness();
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        float glX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
        float glY = 1 - (float)y / glutGet(GLUT_WINDOW_HEIGHT) * 2;

        //boat
        if (glX > -0.5 && glX < 0.5 && glY > -0.55 && glY < -0.35) {
            boatMoving = !boatMoving;
        }

        //birds
        if (glY > 0.7 && glY < 0.9) {
            birdsMoving = !birdsMoving;
        }
    }
}

void idle() {
    if (boatMoving) {
        boatOffset += 0.00005f;
        if (boatOffset > 1.0f) boatOffset = -1.0f;
    }
    if (birdsMoving && timeOfDay != 3) {
        birdOffset += 0.00005f;
        if (birdOffset > 1.0f) birdOffset = -1.0f;
    }
    if (timeOfDay == 3) {
        if (starDim) {
            starBrightness -= 0.00008f;
            if (starBrightness <= 0.3f) starDim = false;
        } else {
            starBrightness += 0.00008f;
            if (starBrightness >= 1.0f) starDim = true;
        }
    }

    glutPostRedisplay();
}

// Circle (used for sun, trees)
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2 * 3.1416 * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}


void drawBoat() {
    glPushMatrix();
    glTranslatef(boatOffset, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(-0.25f, -0.35f, 0.0f);

    // Body
    glColor3f(1.0*brightness, 1.0*brightness, 1.0*brightness);
    glBegin(GL_QUADS);
        glVertex2f(-0.025, -0.04);
        glVertex2f( 0.03,  -0.04);
        glVertex2f( 0.02,   0.07);
        glVertex2f(-0.02,   0.07);
    glEnd();

    // Head
    glColor3f(1.0*brightness, 0.7*brightness, 0.5*brightness);
    glBegin(GL_QUADS);
        glVertex2f(-0.012, 0.07);
        glVertex2f( 0.022, 0.07);
        glVertex2f( 0.022, 0.11);
        glVertex2f(-0.012, 0.11);
    glEnd();

    // Hair
    glColor3f(0.0*brightness, 0.0*brightness, 0.0*brightness);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.015, 0.11);
        glVertex2f( 0.027, 0.11);
        glVertex2f( 0.006, 0.14);
    glEnd();

    // Arm
    glColor3f(0.0*brightness, 0.0*brightness, 0.0*brightness);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.02);
        glVertex2f(0.05, -0.08);
    glEnd();
    glLineWidth(1.0);

    glPopMatrix();


    //  Boat
    glColor3f(0.5*brightness, 0.2*brightness, 0.1*brightness);
    glBegin(GL_POLYGON);
        glVertex2f(-0.20, -0.55);
        glVertex2f( 0.20, -0.55);
        glVertex2f( 0.45, -0.385);
        glVertex2f(-0.45, -0.385);
    glEnd();

    // Mast
    glColor3f(0.4*brightness, 0.2*brightness, 0.0*brightness);
    glBegin(GL_LINES);
        glVertex2f(0.0, -0.385);
        glVertex2f(0.0, -0.20);
    glEnd();

    // Sail
    glColor3f(1.0*brightness, 1.0*brightness, 1.0*brightness);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, -0.20);
        glVertex2f(0.0, -0.385);
        glVertex2f(0.20, -0.385);
    glEnd();
    glPopMatrix();
}


void drawBird(float x, float y) {
    glBegin(GL_LINES);
    glVertex2f(x + birdOffset, y);
    glVertex2f(x + 0.05 + birdOffset, y + 0.03);
    glVertex2f(x + 0.05 + birdOffset, y + 0.03);
    glVertex2f(x + 0.1 + birdOffset, y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (timeOfDay == 0) { // Morning
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.7, 0.4);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
        glColor3f(0.5, 0.7, 1.0);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
        glEnd();
        glColor3f(1.0, 0.8, 0.0);
        drawCircle(0.0, 0.6, 0.1);
    }

    else if (timeOfDay == 1) { // Afternoon
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.5, 0.2);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
        glColor3f(0.2, 0.4, 1.0);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
        glEnd();
        glColor3f(1.0, 0.9, 0.0);
        drawCircle(0.6, 0.7, 0.1);
    }


    else if (timeOfDay == 2) { // Midday
        glBegin(GL_QUADS);
        glColor3f(0.4, 0.7, 1.0);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
        glColor3f(0.2, 0.6, 1.0);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
        glEnd();
        glColor3f(1.0, 1.0, 0.0);
        drawCircle(0.0, 0.9, 0.12);
    }

    else if (timeOfDay == 3) { // Night
        glBegin(GL_QUADS);
        glColor3f(0.0, 0.0, 0.2);
        glVertex2f(-1, 0);
        glVertex2f(1, 0);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
        glEnd();

        // Half Moon
        glColor3f(1.0, 1.0, 0.8);
        drawCircle(0.6, 0.7, 0.1);
        glColor3f(0.0, 0.0, 0.0);
        drawCircle(0.63, 0.7, 0.1);

        // Stars (5–6 positions)
        glColor3f(starBrightness, starBrightness, starBrightness);
        drawCircle(-0.5, 0.7, 0.006);
        drawCircle(-0.7, 0.5, 0.006);
        drawCircle(-0.2, 0.95, 0.006);
        drawCircle(0.2, 0.92, 0.006);
        drawCircle(0.5, 0.88, 0.006);
        drawCircle(0.75, 0.93, 0.006);
        drawCircle(-0.3, 0.45, 0.006);
        drawCircle(0.1, 0.5, 0.006);
        drawCircle(0.6, 0.55, 0.006);
        drawCircle(-0.8, 0.42, 0.006);
        drawCircle(-0.8, 0.9, 0.006);
        drawCircle(-0.6, 0.85, 0.006);
        drawCircle(-0.2, 0.95, 0.006);
        drawCircle(0.2, 0.92, 0.006);
        drawCircle(0.5, 0.88, 0.006);
        drawCircle(0.75, 0.93, 0.006);
        drawCircle(-0.3, 0.45, 0.006);
        drawCircle(0.1, 0.5, 0.006);
        drawCircle(0.6, 0.55, 0.006);
        drawCircle(-0.8, 0.42, 0.006);
        drawCircle(-0.4, 0.65, 0.006);
        drawCircle(0.0, 0.6, 0.006);
        drawCircle(0.7, 0.62, 0.006);
        drawCircle(-0.9, 0.58, 0.006);
        }

     // Mountains
    glColor3f(0.4*brightness, 0.3*brightness, 0.3*brightness);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1.0, 0);  glVertex2f(-0.85, 0.45);  glVertex2f(-0.70, 0);
    glVertex2f(-0.90, 0); glVertex2f(-0.65, 0.50);  glVertex2f(-0.40, 0);
    glVertex2f(-0.55, 0); glVertex2f(-0.25, 0.55);  glVertex2f(0.05, 0);
    glVertex2f(-0.10, 0); glVertex2f(0.20, 0.50);   glVertex2f(0.50, 0);
    glVertex2f(0.35, 0);  glVertex2f(0.65, 0.48);   glVertex2f(0.95, 0);
    glVertex2f(0.70, 0);  glVertex2f(1.0, 0.45);    glVertex2f(1.2, 0);
    glEnd();

    // Ground
    glColor3f(0.1*brightness, 0.6*brightness, 0.2*brightness);
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 0);
    glVertex2f(-1, 0);
    glEnd();

    // Curved River
    glColor3f(0.0*brightness, 0.5*brightness, 1.0*brightness);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.6);
    glVertex2f(-0.5, -0.7);
    glVertex2f(0.0, -0.65);
    glVertex2f(0.5, -0.75);
    glVertex2f(1, -0.7);
    glVertex2f(1, -0.2);
    glVertex2f(-1, -0.2);
    glEnd();

    drawBoat();


   // Haystack
    glColor3f(0.9*brightness, 0.8*brightness, 0.2*brightness);

    // Base
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.42, -0.18);
    glVertex2f(-0.32, 0.15);
    glVertex2f(-0.22, -0.18);
    glEnd();

    // Middle
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.37, 0.05);
    glVertex2f(-0.32, 0.25);
    glVertex2f(-0.27, 0.05);
    glEnd();

    // Top
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.34, 0.15);
    glVertex2f(-0.32, 0.30);
    glVertex2f(-0.30, 0.15);
    glEnd();

    // Small stick on top
    glColor3f(0.4, 0.2, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.32, 0.30);
    glVertex2f(-0.32, 0.35);
    glEnd();

    // Small House
    glColor3f(0.7*brightness, 0.3*brightness, 0.2*brightness);
    glBegin(GL_QUADS);
    glVertex2f(-0.85, -0.1);
    glVertex2f(-0.70, -0.1);
    glVertex2f(-0.70, 0.12);
    glVertex2f(-0.85, 0.12);
    glEnd();

    // Roof
    glColor3f(0.4, 0.2, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.88, 0.12);
    glVertex2f(-0.775, 0.28);
    glVertex2f(-0.68, 0.12);
    glEnd();

    // Door
    glColor3f(0.3, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.82, -0.1);
    glVertex2f(-0.78, -0.1);
    glVertex2f(-0.78, 0.0);
    glVertex2f(-0.82, 0.0);
    glEnd();

    // Window
    glColor3f(0.8, 0.9, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.75, 0.0);
    glVertex2f(-0.71, 0.0);
    glVertex2f(-0.71, 0.07);
    glVertex2f(-0.75, 0.07);
    glEnd();

    // tree
    // Trunk
    glColor3f(0.4*brightness, 0.2*brightness, 0.0*brightness);
    glBegin(GL_QUADS);
    glVertex2f(-0.97, -0.2);
    glVertex2f(-0.93, -0.2);
    glVertex2f(-0.93, 0.05);
    glVertex2f(-0.97, 0.05);
    glEnd();

    // Leaves
    glColor3f(0.0*brightness, 0.6*brightness, 0.0*brightness);
    drawCircle(-0.95, 0.15, 0.12);
    drawCircle(-0.91, 0.15, 0.12);
    drawCircle(-0.93, 0.25, 0.14);
    drawCircle(-0.97, 0.25, 0.10);
    drawCircle(-0.89, 0.25, 0.10);
    drawCircle(-0.93, 0.35, 0.08);

    // House
    glColor3f(0.9*brightness, 0.4*brightness, 0.3*brightness);
    glBegin(GL_QUADS);
    glVertex2f(-0.7, -0.2);
    glVertex2f(-0.4, -0.2);
    glVertex2f(-0.4, 0.15);
    glVertex2f(-0.7, 0.15);
    glEnd();

    // Roof
    glColor3f(0.5, 0.2, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.75, 0.15);
    glVertex2f(-0.55, 0.35);
    glVertex2f(-0.35, 0.15);
    glEnd();

    // Door
    glColor3f(0.3, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.58, -0.2);
    glVertex2f(-0.52, -0.2);
    glVertex2f(-0.52, 0.0);
    glVertex2f(-0.58, 0.0);
    glEnd();

    // Window
    glColor3f(0.8, 0.9, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.67, 0.0);
    glVertex2f(-0.6, 0.0);
    glVertex2f(-0.6, 0.08);
    glVertex2f(-0.67, 0.08);
    glEnd();

   // Right side house
    glColor3f(0.9*brightness, 0.4*brightness, 0.3*brightness);
    glBegin(GL_QUADS);
    glVertex2f(0.78, -0.15);
    glVertex2f(1.03, -0.15);
    glVertex2f(1.03, 0.08);
    glVertex2f(0.78, 0.08);
    glEnd();

    // Roof
    glColor3f(0.5, 0.2, 0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.73, 0.08);
    glVertex2f(0.90, 0.22);
    glVertex2f(1.08, 0.08);
    glEnd();

    // Door
    glColor3f(0.3, 0.1, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.89, -0.15);
    glVertex2f(0.93, -0.15);
    glVertex2f(0.93, -0.05);
    glVertex2f(0.89, -0.05);
    glEnd();

    // Window
    glColor3f(0.8, 0.9, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(0.95, 0.00);
    glVertex2f(1.00, 0.00);
    glVertex2f(1.00, 0.06);
    glVertex2f(0.95, 0.06);
    glEnd();

    // Trunk
    glColor3f(0.4*brightness, 0.2*brightness, 0.0*brightness);
    glBegin(GL_QUADS);
    glVertex2f(0.70, -0.2);
    glVertex2f(0.74, -0.2);
    glVertex2f(0.74, 0.05);
    glVertex2f(0.70, 0.05);
    glEnd();

    //Leaves
    glColor3f(0.0*brightness, 0.6*brightness, 0.0*brightness);
    drawCircle(0.76, 0.15, 0.12);
    drawCircle(0.72, 0.22, 0.14);
    drawCircle(0.68, 0.15, 0.12);
    drawCircle(0.74, 0.28, 0.11);
    drawCircle(0.70, 0.08, 0.10);

    // Birds
    glColor3f(0, 0, 0);
    drawBird(-0.2, 0.8);
    drawBird(0.0, 0.75);
    drawBird(0.2, 0.82);

    // Grass details
    glColor3f(0.0*brightness, 0.5*brightness, 0.0*brightness);
    glBegin(GL_LINES);
    for (float x = -1; x < 1; x += 0.05) {
        glVertex2f(x, -0.2);
        glVertex2f(x + 0.01, -0.15);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(900, 600);
    glutCreateWindow("Interactive Day-Night Cycle Scenic View");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


