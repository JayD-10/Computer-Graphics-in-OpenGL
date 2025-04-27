#include <iostream>
#include <math.h>
#include <GL/glut.h>
using namespace std;

int edge, ch;
int xpoint[10], ypoint[10];

double round_val(double d) {
    return floor(d + 0.5);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void translation() {
    int tx, ty;
    cout << "\tEnter Tx, Ty: ";
    cin >> tx >> ty;

    for (int i = 0; i < edge; i++) {
        xpoint[i] += tx;
        ypoint[i] += ty;
    }

    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        glVertex2i(xpoint[i], ypoint[i]);
    }
    glEnd();
    glFlush();
}

void rotation() {
    int cx, cy;
    cout << "\nEnter arbitrary point (x, y): ";
    cin >> cx >> cy;

    cx = cx + 320;
    cy = cy + 240;

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(cx, cy);
    glEnd();
    glFlush();

    double theta;
    cout << "\nEnter angle (theta in degrees): ";
    cin >> theta;
    theta = theta * 3.14 / 180;

    glColor3f(0, 0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        int newx = round_val((xpoint[i] - cx) * cos(theta) - (ypoint[i] - cy) * sin(theta) + cx);
        int newy = round_val((xpoint[i] - cx) * sin(theta) + (ypoint[i] - cy) * cos(theta) + cy);
        glVertex2i(newx, newy);
    }
    glEnd();
    glFlush();
}

void scale() {
    glColor3f(1.0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        glVertex2i(xpoint[i], ypoint[i]);
    }
    glEnd();
    glFlush();

    cout << "\n\tScaling (origin at center: 320,240)\n";
    int sx, sy;
    cout << "\tEnter Sx, Sy: ";
    cin >> sx >> sy;

    for (int i = 0; i < edge; i++) {
        xpoint[i] = ((xpoint[i] - 320) * sx) + 320;
        ypoint[i] = ((ypoint[i] - 240) * sy) + 240;
    }

    glColor3f(0, 0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        glVertex2i(xpoint[i], ypoint[i]);
    }
    glEnd();
    glFlush();
}

void reflection() {
    char axis;
    cout << "Enter Reflection Axis (x or y): ";
    cin >> axis;

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < edge; i++) {
        if (axis == 'x' || axis == 'X') {
            glVertex2i(xpoint[i], (ypoint[i] * -1) + 480);
        } else if (axis == 'y' || axis == 'Y') {
            glVertex2i((xpoint[i] * -1) + 640, ypoint[i]);
        }
    }
    glEnd();
    glFlush();
}

void Draw() {
    if (ch == 2 || ch == 3 || ch == 4) {
        glColor3f(1.0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(0, 240); glVertex2i(640, 240);
        glVertex2i(320, 0); glVertex2i(320, 480);
        glEnd();
        glFlush();

        glColor3f(1.0, 0, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < edge; i++) {
            glVertex2i(xpoint[i], ypoint[i]);
        }
        glEnd();
        glFlush();
    }

    if (ch == 1) {
        scale();
    } else if (ch == 2) {
        rotation();
    } else if (ch == 3) {
        reflection();
    } else if (ch == 4) {
        translation();
    }
}

int main(int argc, char **argv) {
    cout << "\n\tEnter:\n";
    cout << "1) Scaling\n";
    cout << "2) Rotation about arbitrary point\n";
    cout << "3) Reflection\n";
    cout << "4) Translation\n";
    cout << "\tYour choice: ";
    cin >> ch;

    if (ch >= 1 && ch <= 4) {
        cout << "Enter number of edges: ";
        cin >> edge;

        int x, y;
        cout << "Enter " << edge << " polygon points (x y):\n";
        for (int i = 0; i < edge; i++) {
            cout << "Point " << (i + 1) << ": ";
            cin >> x >> y;
            xpoint[i] = x + 320;
            ypoint[i] = y + 240;
        }

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(640, 480);
        glutInitWindowPosition(200, 200);
        glutCreateWindow("2D Transformations");
        init();
        glutDisplayFunc(Draw);
        glutMainLoop();
        return 0;
    } else {
        cout << "\n\tInvalid input. Run again.\n";
        return 0;
    }
}

