//Adding the Libraries.
#include<iostream>
#include<ctime>
#include<math.h>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<string>

using namespace std;
//functions:
void writegameintro() {
    ofstream introfile("gameintro.txt");
    if (!introfile) {
        cout << "Error opening game intro file." << endl;
        return;
    }
    introfile << "Welcome to Pac-Man Game" << endl;
    introfile << "Your goal is to collect all pallets." << endl;
    introfile << "Use W, D, S, A for movement." << endl;
    introfile.close();
}
void gameintroread() {
    ifstream introfile("gameintro.txt");
    if (!introfile) {
        cout << "Error opening game intro file." << endl;
        return;
    }
    system("CLS");
    string line;
    while (getline(introfile, line)) {
        cout << line << endl;
    }
    introfile.close();
    cout << "Enter any key to start..." << endl;
    cin.ignore();
}

void clearScreen() {
    system("cls");
}
void generateMap(char arr[20][20], int& count, int ran) {
    for (int x = 0; x < 20; x++)//20 rows
    {
        for (int y = 0; y < 20; y++)//20 columns 
        {
            if (x == 0 || x == 19 || y == 0 || y == 19) //Maze rows and columns
            {
                arr[x][y] = '#';//Wall
            }
            else if (x == ran + 1)// Random obstacle wall-1
            {
                arr[x][y] = '#';
                if (y == 4 || y == 9 || y == 13) //adding pallets in these col
                {
                    arr[x][y] = '.';
                    count++;
                }
            }
            else if (x == ran + 3)// Random obstacle wall-2
            {
                arr[x][y] = '#';
                if (y == 3 || y == 7 || y == 13)//adding pallets in these col
                {
                    arr[x][y] = '.';
                    count++;
                }
            }
            else if (x == ran + 9)//Random obstacle wall-3
            {
                arr[x][y] = '#';
                if (y == 4 || y == 9 || y == 13)// adding pallets in these col 
                {
                    arr[x][y] = '.';
                    count++;
                }
            }
            else {
                arr[x][y] = '.';//adding overall pallets
                count++;
            }
        }
    }
}
void printMap(char arr[20][20], int gr1, int gc1, int gr2, int gc2, int score) {
    char ghost1 = 'G', ghost2 = 'G';//Intializing
    for (int x = 0; x < 20; x++)//rows
    {
        for (int y = 0; y < 20; y++)//columns
        {
            if (x == gr1 && y == gc1)
                cout << "\033[1;34m" << ghost1 << " ";//Blue Ghost
            else if (x == gr2 && y == gc2)
                cout << "\033[1;34m" << ghost2 << " ";//Blue Ghost
            else if (arr[x][y] == '#')
                cout << "\033[1;32m" << arr[x][y] << " ";//Green Walls
            else if (arr[x][y] == '.')
                cout << "\033[1;32m" << arr[x][y] << " ";//Green Walls
            else if (arr[x][y] == 'P' || arr[x][y] == '^' || arr[x][y] == 'v' || arr[x][y] == '<' || arr[x][y] == '>')
                cout << "\033[1;31m" << arr[x][y] << " ";//Red pacman
            else
                cout << "\033[0m" << arr[x][y] << " ";
        }
        cout << endl;
    }
}
//write file
void savescore(int score) {
    ofstream scorefile("score.txt", ios::app);//Add new scores without disturbing the previous ones.
    if (!scorefile) {
        cout << "Error saving score." << endl;
        return;
    }
    scorefile << score << endl;
    scorefile.close();
}
//read file
void readscores() {
    ifstream scorefile("score.txt");
    if (!scorefile) {
        cout << "No score history found." << endl;
        return;
    }
    cout << "\nPrevious Scores:\n";
    int s;
    while (scorefile >> s)//Displays the scores line by line.
    {
        cout << "- " << s << endl;
    }
    scorefile.close();
}
//write file
void deletescores() {
    ofstream scorefile("score.txt", ios::trunc);//Mode for deleting the overall scores
    if (!scorefile) {
        cout << "Error deleting scores." << endl;
        return;
    }
    cout << "All scores deleted successfully.\n";
    scorefile.close();
}
//read file
int highscore() {
    ifstream scorefile("score.txt");
    int highscore = 0, temp;//temporary storing the value
    if (!scorefile) {
        return 0;
    }
    while (scorefile >> temp) {
        if (temp > highscore)
            highscore = temp;
    }
    scorefile.close();
    return highscore;
}
int main() {
    writegameintro();
    gameintroread();
    //Assigning the variabes.

    char arr[20][20];//Maze size 20X20 (20rows,20columns)
    int x, y, a = 1, b = 1, count = 0, score = 0;
    char move;
    srand(time(0));
    int gc1 = 18, gr1 = 10, gc2 = 3, gr2 = 9;//initial positions of the ghost
    char ghost1 = 'G';
    char ghost2 = 'G';
    char pacman = 'P';
    int ran = (rand() % 5 + 3);
    //calling of the function
    generateMap(arr, count, ran);
    arr[b][a] = pacman;//initial position of pacman

    cout << "\t\t\tScore: " << score << endl;
    cout << "\t\t\tHigh Score: " << highscore() << endl;
    printMap(arr, gr1, gc1, gr2, gc2, score);//function calling
    //infinite loop for taking user moves
    for (int m=0;m==0;) {
        cout << "\nEnter Move (W/A/S/D): ";
        if (score == count - 1)//winnig condition: all pallets are collected
        {
            cout << "Game over, You Win!" << endl;
            cout << "\tYour Score: " << score << endl;
            cout << "High Score: " << highscore() << endl;
            savescore(score);
            break;
        }

        move = _getch();//ask for user move

        if (move == 's')//move down 
        {
            b++;
            if (b < 19)//keep within bounds
            {
                arr[b - 1][a] = ' ';
                if (arr[b][a] == '#')//prevent from moving into walls
                    b--;
            }
        }
        else if (move == 'w')//move up 
        {
            b--;
            if (b >= 0) //keep within bounds
            {
                arr[b + 1][a] = ' ';
                if (arr[b][a] == '#')//preventing from moveing into walls
                    b++;
            }
        }
        else if (move == 'a') //left move
        {
            a--;
            if (a >= 0) //keep within bounds
            {
                arr[b][a + 1] = ' ';
                if (arr[b][a] == '#')//preventing from moving into walls
                    a++;
            }
        }
        else if (move == 'd')//right move
        {
            a++;
            if (a < 19)//keep within bounds
            {
                arr[b][a - 1] = ' ';
                if (arr[b][a] == '#')//preventing from moving into walls
                    a--;
            }
        }
        //hitng the wall
        if (arr[b][a] == '#') {
            cout << "\nYou hit a wall. Game over!" << endl;
            cout << "\tYour score is: " << score << endl;
            cout << "High Score: " << highscore() << endl;
            savescore(score);
            break;
        }
        //collecting pallets

        if (arr[b][a] == '.') {
            score++;
        }
        //Ghost1 chasing the Pacman(gr1,gc1)

        if (rand() % 2 == 0) {
            if (b < gr1) gr1--;
            else if (b > gr1) gr1++;
        }
        else {
            if (a < gc1) gc1--;
            else if (a > gc1) gc1++;
        }
        //Ghost2 chasing the Pacman(gr2,gc2)

        if (rand() % 2 == 0) {
            if (b < gr2) gr2--;
            else if (b > gr2) gr2++;
        }
        else {
            if (a < gc2) gc2--;
            else if (a > gc2) gc2++;
        }
        //if caught by ghost

        if ((b == gr1 && a == gc1) || (b == gr2 && a == gc2)) {
            cout << "Game over!" << endl;
            cout << "\tYour Score: " << score << endl;
            cout << "High Score: " << highscore() << endl;
            savescore(score);
            break;
        }

        clearScreen();// Clear the screen for the next round of display
        
        // Assigning the shapes for Pacman (up/down/left/right arrows) and move


        if (move == 's') pacman = 'v';//pacman facing down
        else if (move == 'w') pacman = '^';//pacman facing up
        else if (move == 'd') pacman = '>';//pacman facing right
        else if (move == 'a') pacman = '<';//pacman facing left
        else cout << "Invalid Move!";
        arr[b][a] = pacman;

        cout << "\t\t\tScore: " << score << endl;
        cout << "\t\t\tHigh Score: " << highscore() << endl;
        printMap(arr, gr1, gc1, gr2, gc2, score);//printing the maze after the move
    }
    //asking for user choice
    char choice;
    cout << "\nDo you want to view past scores? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        readscores();//function calling
    }

    cout << "\nDo you want to delete all past scores? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        deletescores();//function calling
    }

    return 0;
}






