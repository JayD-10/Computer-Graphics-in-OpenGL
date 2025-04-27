#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

double x, y, len, angle;
int it;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);      // Set coordinate system
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawLine(int x1, int y1, int x2, int y2) {
    glColor3f(0, 1, 0); // Green color
    glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void k_curve(double x, double y, double len, double angle, int it) {
    if (it > 0) {
        len /= 3.0;

        // First segment
        k_curve(x, y, len, angle, it - 1);
        x += len * cos(angle * M_PI / 180.0);
        y += len * sin(angle * M_PI / 180.0);

        // Second segment - turn +60 degrees
        k_curve(x, y, len, angle + 60.0, it - 1);
        x += len * cos((angle + 60.0) * M_PI / 180.0);
        y += len * sin((angle + 60.0) * M_PI / 180.0);

        // Third segment - turn -60 degrees
        k_curve(x, y, len, angle - 60.0, it - 1);
        x += len * cos((angle - 60.0) * M_PI / 180.0);
        y += len * sin((angle - 60.0) * M_PI / 180.0);

        // Fourth segment
        k_curve(x, y, len, angle, it - 1);
    }
    else {
        int x2 = int(x + len * cos(angle * M_PI / 180.0) + 0.5);
        int y2 = int(y + len * sin(angle * M_PI / 180.0) + 0.5);
        drawLine(int(x + 0.5), int(y + 0.5), x2, y2);
    }
}

void display() {
    k_curve(x, y, len, angle, it);
}

int main(int argc, char** argv) {
    cout << "Enter Starting Point (x y): ";
    cin >> x >> y;
    cout << "Enter Length of line and Angle: ";
    cin >> len >> angle;
    cout << "Enter Number of Iterations: ";
    cin >> it;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Koch Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

/*
for explaination of code pls refer
https://chatgpt.com/share/6806f4bc-ff2c-8010-a684-0b93568b3810
*/
