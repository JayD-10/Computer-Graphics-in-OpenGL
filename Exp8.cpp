#include <GL/glut.h>

float x = -0.9; // Initial X position

void init() {
    glClearColor(1, 1, 1, 1); // White background
    gluOrtho2D(-1, 1, -1, 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0); // Red color

    glBegin(GL_POLYGON);
    glVertex2f(x, 0.0);
    glVertex2f(x + 0.2, 0.0);
    glVertex2f(x + 0.2, 0.2);
    glVertex2f(x, 0.2);
    glEnd();

    glutSwapBuffers();
}

void update(int) {
    x += 0.01;
    if (x > 1.0) x = -1.0; // Loop back

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Moving Square");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}

