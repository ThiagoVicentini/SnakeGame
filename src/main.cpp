#include <GL/glut.h>
#include <time.h>
#include <deque>

#define FPS 10

using namespace std;

int cellSize = 20;
int cellCount = 40;
int offset = 2;

bool IsPairsEquals(pair<int, int> onePair, pair<int, int> otherPair){
    if(onePair.first == otherPair.first && onePair.second == otherPair.second)
        return true;
    return false;
}

pair<int, int> addPair(pair<int, int> onePair, pair<int, int> otherPair){
    int firstValue = onePair.first + otherPair.first;
    int secondValue = onePair.second + otherPair.second;
    return make_pair(firstValue, secondValue);
}

bool ElementInDeque(pair<int, int> element, deque<pair<int, int>> deque) {
    for(unsigned int i=0; i<deque.size(); i++)
        if(IsPairsEquals(element, deque[i]))
            return true;

    return false;
}

class Snake {
public:
    deque<pair<int, int>> body = {{6, 9}, {5, 9}, {4, 9}};
    pair<int, int> direction = {1,0};
    bool addSegment = false;

    void Draw(){
        for(unsigned int i=0; i<body.size(); i++){
            int x = body[i].first;
            int y = body[i].second;
            glColor3d(43/255.0, 51/255.0, 24/255.0);
            glRectd(x+offset, y+offset, x+1+offset, y+1+offset);
        }
    }

    void Update() {
        body.push_front(addPair(body[0], direction));
        if(addSegment) {
            addSegment = false;
        } else {
            body.pop_back();
        }
    }

    void Reset() {
        body = {{6, 9}, {5, 9}, {4, 9}};
        direction = {1, 0};
    }
};

class Food {
public:
    pair<int, int> position;

    Food(deque<pair<int, int>> snakeBody){
        position = GenerateRandomPos(snakeBody);
    }

    ~Food(){
    }

    void Draw() {
        glColor3d(1.0, 0.0, 0.0);
        glRectd(position.first+offset, position.second+offset, position.first+1+offset, position.second+1+offset);
    }

    int GetRandomValue(int min, int max) {
        return min + rand()%(max-min);
    }

    pair<int, int> GenerateRandomCell() {
        int x = GetRandomValue(0, cellCount-2-offset);
        int y = GetRandomValue(0, cellCount-2-offset);

        return make_pair(x, y);
    }

    pair<int, int> GenerateRandomPos(deque<pair<int, int>> snakeBody){
        pair<int, int> position = GenerateRandomCell();
        while(ElementInDeque(position, snakeBody)){
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;

    void Draw() {
        food.Draw();
        snake.Draw();
    }

    void Update() {
        if(running) { 
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood() {
        if(IsPairsEquals(snake.body[0], food.position)) {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score++;
        }
    }

    void CheckCollisionWithEdges() {
        if(snake.body[0].first == cellCount-2-offset || snake.body[0].first == -1) {
            GameOver();
        }
        if(snake.body[0].second == cellCount-2-offset || snake.body[0].second == -1) {
            GameOver();
        }
    }

    void CheckCollisionWithTail() {
        deque<pair<int, int>> headlessBody = snake.body;
        headlessBody.pop_front();
        if(ElementInDeque(snake.body[0], headlessBody))
            GameOver();
    }

    void GameOver() {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
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
    glBegin(GL_LINE_LOOP);
        glVertex2f(offset, offset);
        glVertex2f(cellCount-offset, offset);
        glVertex2f(cellCount-offset, cellCount-offset);
        glVertex2f(offset, cellCount-offset);
    glEnd();
    
    glColor3f(.0, .0, .0);
    glRasterPos2f(offset, 0.5);
    char string[10];
    sprintf(string, "%d", game.score);
    int i = 0;
    while(string[i]){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i++]);
    }
    
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
            game.running = true;
            break;
        case GLUT_KEY_DOWN: 
            if(game.snake.direction.second != 1)
                game.snake.direction = {0, -1};
            game.running = true;
            break;
        case GLUT_KEY_LEFT: 
            if(game.snake.direction.first != 1)
                game.snake.direction = {-1, 0};
            game.running = true;
            break;
        case GLUT_KEY_RIGHT: 
            if(game.snake.direction.first != -1)
                game.snake.direction = {1, 0};
            game.running = true;
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(cellSize*cellCount+2*offset, cellSize*cellCount+2*offset);
    glutCreateWindow("Snake game");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;
}