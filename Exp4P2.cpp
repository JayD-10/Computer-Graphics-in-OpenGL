#include <iostream>
#include <math.h>
#include <GL/glut.h>

struct Point {
    GLint x;
    GLint y;
};

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
    Color color = getPixelColor(x, y);

    if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b) {
        setPixelColor(x, y, newColor);
        floodFill(x+1, y, oldColor, newColor);
        floodFill(x-1, y, oldColor, newColor);
        floodFill(x, y+1, oldColor, newColor);
        floodFill(x, y-1, oldColor, newColor);
    }
}

void onMouseClick(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 480 - y; // Convert window to OpenGL coordinates
        Color newColor = {1.0f, 0.0f, 0.0f}; // Red
        Color oldColor = getPixelColor(x, y);
        floodFill(x, y, oldColor, newColor);
    }
}

void draw_circle(Point pC, GLfloat radius) {
    GLfloat x, y;
    for (float theta = 0.0; theta <= 2 * M_PI; theta += 0.001) {
        x = pC.x + radius * cos(theta);
        y = pC.y + radius * sin(theta);
        glVertex2i(x, y);
    }
}

void display(void) {
    Point pt = {320, 240};
    GLfloat radius = 100;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    draw_circle(pt, radius);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Flood Fill - OpenGL");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutMainLoop();
    return 0;
}

