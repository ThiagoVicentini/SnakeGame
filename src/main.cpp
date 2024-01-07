#include <GL/glut.h>
#include <deque>

#define FPS 10

using namespace std;

int cellSize = 20;
int cellCount = 40;

class Snake {
public:
    deque<pair<int, int>> body = {{6, 9}, {5, 9}, {4, 9}};
    
    void Draw(){
        for(unsigned int i=0; i<body.size(); i++){
            int x = body[i].first;
            int y = body[i].second;
            glColor3d(43/255.0, 51/255.0, 24/255.0);
            glRectd(x, y, x+1, y+1);
        }
    }
};

};

void init(){
    glClearColor(173/255.0, 204/255.0, 96/255.0, 1);
}

void reshape(GLsizei w, GLsizei h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, cellCount, 0.0, cellCount, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    // Drawing
    glutSwapBuffers();
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
    glutInitWindowSize(cellSize*cellCount, cellSize*cellCount);
    glutCreateWindow("Snake game");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}