#include <GL/glut.h>
#include <stdio.h>

#define FRAME_W 300
#define FRAME_H 300

void renderPixel(int orig_x, int orig_y, GLclampf r, GLclampf g, GLclampf b) {
    glBegin(GL_POINTS);
        glColor3f(r, g, b);
        float ox = (double)orig_x/(FRAME_W/2) - 1;
        float oy = -((double)orig_y/(FRAME_H/2) - 1);
        glVertex2f(ox, oy);
    glEnd();
} 

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderPixel(30, 30, 1, 1, 0);
    renderPixel(100, 100, 0, 1, 0);
    renderPixel(200, 200, 0, 0, 1);
    renderPixel(270, 270, 0, 0, 1);
    renderPixel(290, 290, 1, 0, 1);

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(FRAME_W, FRAME_H);
    glutCreateWindow("CG 2018");
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
