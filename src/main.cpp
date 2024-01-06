#include <GL/glut.h>

#define COLUMNS 40.0
#define ROWS 40.0
#define FPS 10

using namespace std;

float w = 500, h = 500;

void init(){
    glClearColor(0, 0, 0, 1);
}

void reshape(GLsizei w, GLsizei h){
}

void display(){
}

void timer(int t){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
}

void keyboard(int key, int x, int y){
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(w, h);
    glutCreateWindow("Snake game");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}