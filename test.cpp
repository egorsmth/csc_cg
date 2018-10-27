#include "drawing.cpp"



void Display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //renderPixel(30, 30, 1, 1, 0);
    //renderPixel(100, 100, 0, 1, 0);
    //renderPixel(200, 200, 0, 0, 1);
    //renderPixel(270, 270, 0, 0, 1);
    //renderPixel(290, 290, RED);
    // drawCircle(100, 100, 10, RED);
    drawLine(10, 100, 100, 10, RED);
    drawLine(10, 100, 100, 210, RED);
    drawLine(100, 10, 210, 100, RED);
    drawLine(100, 210, 210, 100, RED);
    FloodFill(200, 100, 0, 0.5, 1);
    //drawLine(250, 5, 100, 100, RED);
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
