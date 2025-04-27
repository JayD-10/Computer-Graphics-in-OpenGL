#include<iostream>
#include<GL/glut.h>
#include<math.h>
using namespace std;

int xl=50,xh=200,yl=50,yh=200;
int flag=0;
float u1,v1,u2,v2;

struct code {
    int t, b, r, l;
};

void init() {
    glClearColor(1,1,1,0); // white background
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0); // black color
    glFlush();
}

code get_code(int u, int v) {
    code c = {0,0,0,0};
    if(u < xl) c.l = 1;
    if(u > xh) c.r = 1;
    if(v < yl) c.b = 1;
    if(v > yh) c.t = 1;
    return c;
}

// DDA Line Drawing
void line(float u1, float v1, float u2, float v2) {
    float dx, dy, x = u1, y = v1, xi, yi;
    int steps, i;
    
    dx = u2 - u1;
    dy = v2 - v1;
    
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    xi = dx / (float)steps;
    yi = dy / (float)steps;
    
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    
    for(i = 0; i < steps; i++) {
        x += xi;
        y += yi;
        glVertex2f(x, y);
    }
    
    glEnd();
    glFlush();
}

// Draw clipping window
void draw_window() {
    line(xl, yl, xh, yl); // bottom
    line(xl, yl, xl, yh); // left
    line(xh, yl, xh, yh); // right
    line(xl, yh, xh, yh); // top
}

// Mouse callback to get line input
void mymouse(int button, int state, int x, int y) {
    glColor3f(0, 0, 0);
    if(state == GLUT_DOWN && flag == 0) {
        u1 = x; 
        v1 = 480 - y;
        flag = 1;
    } else if(state == GLUT_DOWN && flag == 1) {
        u2 = x;
        v2 = 480 - y;
        flag = 2;
        line(u1, v1, u2, v2);
    }
}

// Cohen-Sutherland Line Clipping Algorithm
void cohen() {
    code c1, c2, c;
    float m;
    int xi, yi, flag_local;
    
    if (u2 - u1 != 0)
        m = (v2 - v1) / (u2 - u1);
    else
        m = 99999; // avoid divide by zero for vertical lines
    
    c1 = get_code(u1, v1);
    c2 = get_code(u2, v2);
    
    while(1) {
        if(c1.t==0 && c2.t==0 && c1.b==0 && c2.b==0 && c1.r==0 && c2.r==0 && c1.l==0 && c2.l==0)
            break;
        else if((c1.t && c2.t) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l)) {
            u1 = v1 = u2 = v2 = 0;
            break;
        } else {
            if(c1.l == 1 || c2.l == 1) {
                xi = xl;
                yi = v1 + m * (xl - u1);
                flag_local = (c1.l == 1) ? 0 : 1;
            } else if(c1.r == 1 || c2.r == 1) {
                xi = xh;
                yi = v1 + m * (xh - u1);
                flag_local = (c1.r == 1) ? 0 : 1;
            } else if(c1.b == 1 || c2.b == 1) {
                xi = u1 + (1.0 / m) * (yl - v1);
                yi = yl;
                flag_local = (c1.b == 1) ? 0 : 1;
            } else if(c1.t == 1 || c2.t == 1) {
                xi = u1 + (1.0 / m) * (yh - v1);
                yi = yh;
                flag_local = (c1.t == 1) ? 0 : 1;
            }

            c = get_code(xi, yi);

            if(flag_local == 0) {
                u1 = xi;
                v1 = yi;
                c1 = c;
            } else {
                u2 = xi;
                v2 = yi;
                c2 = c;
            }
        }
    }

    draw_window();
    line(u1, v1, u2, v2);
}

// Keyboard input
void mykey(unsigned char key, int x, int y) {
    if(key == 'c') {
        init();
        cohen();
    } else if(key == 'r') {
        init();
        draw_window();
        flag = 0;
    }
}

// Display callback (needed to prevent error)
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_window();
    glFlush();
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line_Clipping");
    
    gluOrtho2D(0, 640, 0, 480);
    
    glutDisplayFunc(display); // required display function
    init();
    draw_window();
    
    glutMouseFunc(mymouse);
    glutKeyboardFunc(mykey);
    
    glutMainLoop();
    return 0;
}

