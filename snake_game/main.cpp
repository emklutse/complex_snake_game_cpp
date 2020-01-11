/*
snake game created without classes, hence will not be object oriented
*/
#include <iostream>
#include <windows.h>

/*cons all input and output, has 2 functions that were gonna use 
(asynchronous functions that don't block the program used for getting a character from a console window)*/
#include <conio.h>

using namespace std;

//global variable
bool gameOver;
//variables for map dimensions
const int width = 20;
const int height = 20;
//variables for head position
int x, y;
//variables for fruit position
int fruitX, fruitY;
//variable for score
int score;
//for tracking the direction of the snake
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
//holds direction of snake
eDirection dir;

int tailX[100], tailY[100];
int nTail;

void Setup() {
    gameOver = false;
    // snake will not move until we start moving it
    dir = STOP;
    //set position of head to be centred
    x = width / 2;
    y = height / 2;
    //randomly places fruit somewehere on the map
    fruitX = rand() % width;
    fruitY = rand() % height;
    //sets score to 0
    score = 0;
}

//draws the map
void Draw() 
{
    //clears console window/terminal
    system("cls");

    //prints top wall of map
    for (int i = 0; i < width+2; i++) 
        cout << "#";
    cout << endl;

    //prints map, just like printing a matrix
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }                   
                }
                if (!print)
                        cout << " ";
                
            }

            if (j == width - 1) 
                cout << "#";
        }
        cout << endl;
    }

    //prints bottom wall of map
    for (int i = 0; i < width+2; i++) 
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

void Input() {
    //returns a boolean, positive number when keyboard is pressed. If nothing is pressed, returns 0
    if (_kbhit()) {
        //returns the ASCII value of characer pressed
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    //game over when you hit the wall
        /*if (x > width || x < 0 || y>height ||y<0) 
            gameOver = true;*/

    //no game over when you hit the wall. come from the other section of wall when it hits a opposite of the wall
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) x = height - 1;

    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        //randomly places fruit somewehere on the map
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    
}


int main() {
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); //sleep(10);
    }
    return 0;
}