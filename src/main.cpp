#include <GL/glut.h>
#include <time.h>
#include <deque>

#define FPS 10

using namespace std;

int cellSize = 20;
int cellCount = 40;

pair<int, int> addPair(pair<int, int> onePair, pair<int, int> otherPair){
    int firstValue = onePair.first + otherPair.first;
    int secondValue = onePair.second + otherPair.second;
    return make_pair(firstValue, secondValue);
}

class Snake {
public:
    deque<pair<int, int>> body = {{6, 9}, {5, 9}, {4, 9}};
    pair<int, int> direction = {1,0};

    void Draw(){
        for(unsigned int i=0; i<body.size(); i++){
            int x = body[i].first;
            int y = body[i].second;
            glColor3d(43/255.0, 51/255.0, 24/255.0);
            glRectd(x, y, x+1, y+1);
        }
    }

    void Update() {
        body.push_front(addPair(body[0], direction));
        body.pop_back();
    }
};

class Food {
public:
    pair<int, int> position;

    Food(){
        position = GenerateRandomPos();
    }

    ~Food(){
    }

    void Draw() {
        glColor3d(1.0, 0.0, 0.0);
        glRectd(position.first, position.second, position.first+1, position.second+1);
    }

    int GetRandomValue(int min, int max) {
        return min + rand()%(max-min);
    }

    pair<int, int> GenerateRandomPos(){
        int x = GetRandomValue(1, cellCount-2);
        int y = GetRandomValue(1, cellCount-2);
        return make_pair(x, y);
    }
};

class Game {
public:
    Snake snake = Snake();
    Food food = Food();

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        snake.Update();
    }
};

Game game = Game();

void init(){
    glClearColor(173/255.0, 204/255.0, 96/255.0, 1);
    srand(time(NULL));
}

void reshape(GLsizei w, GLsizei h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, cellCount, 0.0, cellCount, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    game.Update();
    glClear(GL_COLOR_BUFFER_BIT);
    // Drawing
    game.Draw();
    glutSwapBuffers();
}

void timer(int t){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
}

void keyboard(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP: 
            if(game.snake.direction.second != -1)
                game.snake.direction = {0, 1};
            break;
        case GLUT_KEY_DOWN: 
            if(game.snake.direction.second != 1)
                game.snake.direction = {0, -1};
            break;
        case GLUT_KEY_LEFT: 
            if(game.snake.direction.first != 1)
                game.snake.direction = {-1, 0};
            break;
        case GLUT_KEY_RIGHT: 
            if(game.snake.direction.first != -1)
                game.snake.direction = {1, 0};
            break;
        default:
            break;
    }

    glutPostRedisplay();
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