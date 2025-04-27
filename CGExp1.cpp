#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// Global variables for storing points and line style
int x1_coord, y1_coord, x2_coord, y2_coord;
bool firstClick = true;
int lineStyle = 1; // 1: Simple, 2: Dotted, 3: Dashed, 4: Solid

// Function to set a pixel in OpenGL
void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to draw axes (X and Y)
void drawAxes() {
    glColor3f(1.0, 1.0, 1.0); // White color
    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}

// DDA Line Drawing Algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    
    float x = x1, y = y1;
    
    for (int i = 0; i <= steps; i++) {
        if (lineStyle == 1 || lineStyle == 4 || (lineStyle == 2 && i % 5 == 0) || (lineStyle == 3 && i % 10 < 5)) {
            setPixel(round(x), round(y));
        }
        x += xInc;
        y += yInc;
    }
}

// Bresenham's Line Drawing Algorithm
void drawLineBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x2 >= x1) ? 1 : -1;
    int sy = (y2 >= y1) ? 1 : -1;
    int err = dx - dy;
    
    int count = 0;
    while (true) {
        if (lineStyle == 1 || lineStyle == 4 || (lineStyle == 2 && count % 5 == 0) || (lineStyle == 3 && count % 10 < 5)) {
            setPixel(x1, y1);
        }
        if (x1 == x2 && y1 == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
        count++;
    }
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    glFlush();
}

// Mouse callback function to get user clicks for drawing lines
void mouseClick(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int x = mx - 500;  // Convert to OpenGL coordinate
        int y = 500 - my;  // Convert to OpenGL coordinate

        if (firstClick) {
            x1_coord = x;
            y1_coord = y;
            firstClick = false;
        } else {
            x2_coord = x;
            y2_coord = y;
            firstClick = true;

            glColor3f(1.0, 0.0, 0.0); // Red color for line

            // Uncomment one of the below methods as per requirement
            drawLineDDA(x1_coord, y1_coord, x2_coord, y2_coord);
            // drawLineBresenham(x1_coord, y1_coord, x2_coord, y2_coord);

            glFlush();
        }
    }
}

// Keyboard callback function to change line styles
void keyboard(unsigned char key, int, int) {
    if (key == '1') lineStyle = 1; // Simple
    if (key == '2') lineStyle = 2; // Dotted
    if (key == '3') lineStyle = 3; // Dashed
    if (key == '4') lineStyle = 4; // Solid
    cout << "Line Style Changed: " << lineStyle << endl;
}

// OpenGL initialization function
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glColor3f(1.0, 1.0, 1.0);         // White drawing color
    gluOrtho2D(-500, 500, -500, 500); // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("DDA & Bresenham Line Drawing - OpenGL");

    initOpenGL();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}

