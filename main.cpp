#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "clui.h"
using namespace std;

void printBoard();
void printHome(int i , int j);
void checkAroundBombs();
void assignBomb();
void setFirstPrintState();
void getInput();
void move(char input);
void registerUser();
void choosingProfile(int mode);
int findEmptyProfile();
void deleteProfile();
int profileNameInputCheck(char* name);
void mainMenu();
void printMainmenu();
void printMineSweeper();
void customGame();
bool RCMCheck(int input , int a , int b);
void creatingGameBoardAndMines();
void leaderBoard();
void swap(string *a, string *b);
void swap(int *a, int *b) ;
void changeName();
void help();
void newGame();
void openAroundSafeHouses(int i , int j);
void game();
void playerLose();
void playerWon();
void printYouWon();
void printYouLose();
void pauseMenu();
void printPauseMenu();
void saveGame();
int createSaveSlot(int nslots);
void deleteSaveSlot(int nslots);
void loadGame();
int saveSlotNameCheck(char* name , int n);
void loading();
void printLoading();
void printHelp();
void printLeaderBoard();
void printProfiles();
void printNewGame();

int** bombs;
int** homesPrintMode;
int** aroundBombsCount;
int width = 0;
int height = 0;
int numberOfBombs , numberOfCloseSafeHouses , numberOfRemainingFlags;
int matchScore;
int x , y;
string currentPlayer = "";
int gameState = 0;
int currentSave;

/*
homes Print Modes:
0 -> ?
1 -> Opened
2 -> Exploded Bomb
3 -> Flag
*/

/*
Choosing profile parameters:
0 -> choosing when game starts or after deleting the current user. -> delete option won't show.
1 -> choosing from the menu. -> we have delete option.
*/

int main()
{
    srand(time(0));

    choosingProfile(0);
}

void printBoard()
{
    clear_screen();
    cursor_to_pos(1 , 1);
    for (int i = 0; i < height; i++)
    {
        if(gameState == 1) change_color_rgb(0,255,0);
        if(gameState == 0) change_color_rgb(255, 255, 0);
        if(gameState == -1) change_color_rgb(255,0,0);
        for (int j = 0; j < width*4 + 1; j++)
        {
            cout << '-';
        }
        cout << endl;
        cout << '|';
        reset_color();
        for (int j = 0; j < width; j++)
        {
            cout << ' ';
            printHome(i , j);
            if(gameState == 1) change_color_rgb(0,255,0);
            if(gameState == 0) change_color_rgb(255, 255, 0);
            if(gameState == -1) change_color_rgb(255,0,0);
            cout << " |";
            reset_color();
        }
        cout << endl;
    }
    for (int i = 0; i < width*4 + 1; i++)
    {
        if(gameState == 1) change_color_rgb(0,255,0);
        if(gameState == 0) change_color_rgb(255, 255, 0);
        if(gameState == -1) change_color_rgb(255,0,0);
        cout << '-';
        reset_color();
    }
    cout << endl;
    if(gameState == 0)
    {
        int tempScore;
        string tempName;
        cursor_to_pos(1 , width*4 + 6);
        change_color_rgb(0,255,0);
        cout << "* ";
        reset_color();
        change_color_rgb(0,255,255);
        cout << "Remaining Empty Homes";
        reset_color();
        cout << ":\t";
        change_color_rgb(0,255,0); 
        cout << numberOfCloseSafeHouses;
        reset_color();
        cout << "/" ;
        change_color_rgb(255,165,0);
        cout << width * height - numberOfBombs;
        reset_color();

        cursor_to_pos(3 , width*4 + 6);
        change_color_rgb(0,255,0);
        cout << "* ";
        reset_color();
        change_color_rgb(0,255,255);
        cout << "Remaining Flags";
        reset_color();
        cout << ":\t\t";
        change_color_rgb(0,255,0); 
        cout << numberOfRemainingFlags;
        reset_color();
        cout << "/" ;
        change_color_rgb(255,165,0);
        cout << numberOfBombs;
        reset_color();
        ifstream inFile;
        inFile.open(("files/players/" + currentPlayer + "/name.txt") , ios::in);
        inFile >> tempName;
        inFile.close();
        inFile.open(("files/players/" + currentPlayer + "/score.txt") , ios::in);
        inFile >> tempScore;
        inFile.close();

        cursor_to_pos(5 , width*4 + 6);
        change_color_rgb(0,255,0);
        cout << "* ";
        reset_color();
        change_color_rgb(0,255,255);
        cout << "player";
        reset_color();
        cout << ":\t\t\t";
        change_color_rgb(0,255,0); 
        cout << tempName;
        reset_color();

        cursor_to_pos(7 , width*4 + 6);
        change_color_rgb(0,255,0);
        cout << "* ";
        reset_color();
        change_color_rgb(0,255,255);
        cout << "Current Score";
        reset_color();
        cout << ":\t\t";
        change_color_rgb(0,255,0); 
        cout << tempScore;
        reset_color();

        cursor_to_pos(9 , width*4 + 6);
        change_color_rgb(0,255,0);
        cout << "* ";
        reset_color();
        change_color_rgb(0,255,255);
        cout << "Score Of This Game";
        reset_color();
        cout << ":\t";
        if(matchScore < 1000) cout << '\t';
        change_color_rgb(0,255,0); 
        cout << matchScore;
        reset_color();
    }
}

void printHome(int i , int j)
{
    switch (homesPrintMode[i][j])
    {
    case 0:
        cout << '?';
        break;
    case 1:
        switch(aroundBombsCount[i][j])
        {
            case 0:
                cout << ' ';
                break;
            case 1:
                change_color_rgb(50 , 124 , 227);
                cout << aroundBombsCount[i][j];
                reset_color();
                break;
            case 2:
                change_color_rgb(255,255,0);
                cout << aroundBombsCount[i][j];
                reset_color();
                break;
            case 3:
            case 4:
            case 5:
                change_color_rgb(255,165,0);
                cout << aroundBombsCount[i][j];
                reset_color();
                break;
            case 6:
            case 7:
            case 8:
                change_color_rgb(128, 0, 128);
                cout << aroundBombsCount[i][j];
                reset_color();
                break;
        }
        break;
    case 2:
        change_color_rgb(255, 0, 0);
        cout << '*';
        reset_color();
        break;
    case 3:
        change_color_rgb(0, 255, 0);
        cout << 'F';
        reset_color();
        break;
    }
}

void checkAroundBombs()
{
    int mineCount;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mineCount = 0;
            if (i - 1 >= 0)
            {
                if (j - 1 >= 0)
                {
                    if (bombs[i - 1][j - 1] == 1)
                        mineCount++;
                }
                if (j + 1 < width)
                {
                    if (bombs[i - 1][j + 1] == 1)
                        mineCount++;
                }
                if (bombs[i - 1][j] == 1)
                    mineCount++;
            }
            if (i + 1 < height)
            {
                if (j - 1 >= 0)
                {
                    if (bombs[i + 1][j - 1] == 1)
                        mineCount++;
                }
                if (j + 1 < width)
                {
                    if (bombs[i + 1][j + 1] == 1)
                        mineCount++;
                }
                if (bombs[i + 1][j] == 1)
                    mineCount++;
            }
            if (j - 1 >= 0)
            {
                if (bombs[i][j - 1] == 1)
                    mineCount++;
            }
            if (j + 1 < width)
            {
                if (bombs[i][j + 1] == 1)
                    mineCount++;
            }
            aroundBombsCount[i][j] = mineCount;
        }
    }
}

void assignBomb()
{
    int remainingBombs = numberOfBombs;
    int col, row;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bombs[i][j] = 0;
        }
    }
    while (remainingBombs > 0)
    {
        col = rand() % width;
        row = rand() % height;
        if (bombs[row][col] == 0)
        {
            bombs[row][col] =  1;
            remainingBombs--;
        }
    }
}

void setFirstPrintState()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            homesPrintMode[i][j] = 0;
        }
    }
}

void getInput()
{
    int ix = (y - 2) / 2;
    int iy = (x - 3) / 4;
    char input;
    input = getch();
    switch (input)
    {
    case 'w':
    case 'W':
    case 'a':
    case 'A':
    case 's':
    case 'S':
    case 'd':
    case 'D':
        move(input);
        break;
    case 'f':
    case 'F':
        if(homesPrintMode[ix][iy] == 0)
        {
            if(numberOfRemainingFlags > 0)
            {
                homesPrintMode[ix][iy] = 3;
                numberOfRemainingFlags--;
            }
        }
        else if(homesPrintMode[ix][iy] == 3)
        {
            homesPrintMode[ix][iy] = 0;
            numberOfRemainingFlags++;
        }
        break;
    case ' ':
        if(homesPrintMode[ix][iy] == 0)
        {
            if(bombs[ix][iy] == 0)
            {
                homesPrintMode[ix][iy] = 1;
                numberOfCloseSafeHouses--;
                openAroundSafeHouses(ix , iy);
            }
            else
            {
                playerLose();
                // here player will lose.
            }
        }
        break;
    case 27:
        pauseMenu();
        break;
    }
}

void move(char input)
{
    switch (input)
    {
    case 'w':
    case 'W':
        if(y > 2)
        {
            corsur_up(2);
            y -= 2;
        }
        break;
    case 's':
    case 'S':
        if(y < height * 2)
        {
            cursor_down(2);
            y+=2;
        }
        break;
    case 'a':
    case 'A':
        if(x > 3)
        {
            cursor_backward(4);
            x -= 4;
        }
        break;
    case 'd':
    case 'D':
        if(x < ((width*4)-1))
        {
            cursor_forward(4);
            x += 4;
        }
        break;
    }
}

void registerUser()
{
    clear_screen();
    int temp;
    ifstream inFile;
    inFile.open("files/numberOfRegisteredPlayers.txt" , ios::in);
    int numberOfRegisteredUsers;
    inFile >> numberOfRegisteredUsers;
    if(numberOfRegisteredUsers == 0)
    {
        change_color_rgb(255, 132, 0);
        cout << "There is no registered player. " << "you have to make first profile." << endl;
        reset_color();
    }
    inFile.close();
    string mainPath = "files/players/player";
    mainPath += (char)(findEmptyProfile()+48);
    ofstream outFile;
    char nameStr[100];
    string tempAddr;
    change_color_rgb(140, 255, 0);
    cout << "Please enter your name and then press [Enter]: ";
    reset_color();
    cin.getline(nameStr , 100);
    while (profileNameInputCheck(nameStr) != 1)
    {
        clear_screen();
        if(profileNameInputCheck(nameStr) == 0)
        {
            change_color_rgb(255 , 0 , 0);
            cout << "Wrong input please try again: ";
            reset_color();
        }
        else if(profileNameInputCheck(nameStr) == -1)
        {
            change_color_rgb(255 , 0 , 0);
            cout << "This username have choosed, please try anothe username: ";
            reset_color();
        }
        cin.getline(nameStr , 100);
    }
    
    outFile.open((mainPath+"/name.txt") , ios::out);
    outFile << nameStr;
    outFile.close();
    outFile.open((mainPath + "/score.txt") , ios::out);
    outFile << 0;
    outFile.close();
    outFile.open((mainPath + "/numberOfFilledSlots.txt") , ios::out);
    outFile << 0;
    outFile.close();
    currentPlayer = "player";
    currentPlayer += char(findEmptyProfile()+48);
    inFile.open("files/numberOfRegisteredPlayers.txt" , ios::in);
    inFile >> temp;
    inFile.close();
    temp+=1;
    outFile.open("files/numberOfRegisteredPlayers.txt" , ios::out | ios::trunc);
    outFile << temp;
    outFile.close();
    outFile.open((mainPath + "/regStat.txt") , ios::out | ios::trunc);
    outFile << 1;
    outFile.close();
}

void choosingProfile(int mode)
{
    clear_screen();
    ifstream file;
    string addr;
    char name[10];
    int temp , numberOfPlayers , registeryStatus , profileIterator = 0;
    file.open("files/numberOfRegisteredPlayers.txt" , ios::in);
    file >> numberOfPlayers;
    file.close();
    if(numberOfPlayers == 0)
    {
        registerUser();
    }
    else
    {
        printProfiles();
        change_color_rgb(255, 196, 0);
        cout << "Please choose a profile: " << endl;
        reset_color();
        for (int i = 0 , j = 0; i < 10; i++ , j++)
        {
            addr = "files/players/player";
            addr += (char)(i+48);
            addr += "/regStat.txt";
            file.open(addr , ios::in);
            file >> registeryStatus;
            file.close();
            if(registeryStatus == 1)
            {
                addr = "files/players/player";
                addr += (char)(i+48);
                addr += "/name.txt";

                file.open(addr , ios::in);
                file >> name;

                change_color_rgb(255 , 0 , 0);
                cout << '[';
                reset_color();
                change_color_rgb(0 , 255 , 0);
                cout << j;
                reset_color();
                change_color_rgb(255 , 0 , 0);
                cout << "] ";
                reset_color();
                change_color_rgb(0 , 255 , 255);
                cout << name;
                reset_color();
                cout << endl; 

                file.close();
            }
            else j--;
        }
        if(numberOfPlayers < 10)
        {
            change_color_rgb(255 , 0 , 0);
            cout << '[';
            reset_color();
            change_color_rgb(0 , 255 , 0);
            cout << numberOfPlayers;
            reset_color();
            change_color_rgb(255 , 0 , 0);
            cout << "] ";
            reset_color();
            change_color_rgb(0 , 255 , 0);
            cout << "Create a new profile";
            reset_color();
            cout << endl;
        }
        if(mode == 1)
        {
            change_color_rgb(255 , 0 , 0);
            cout << '[';
            reset_color();
            change_color_rgb(255 , 255 , 0);
            cout << 'r';
            reset_color();
            change_color_rgb(255 , 0 , 0);
            cout << "] ";
            reset_color();
            change_color_rgb(255 , 255 , 0);
            cout << "Change Name";
            reset_color();
            cout << endl;

            change_color_rgb(255 , 0 , 0);
            cout << '[';
            reset_color();
            change_color_rgb(255,69,0);
            cout << 'd';
            reset_color();
            change_color_rgb(255, 0 , 0);
            cout << "] ";
            reset_color();
            change_color_rgb(255,69,0);
            cout << "Delete a profile";
            reset_color();
            cout << endl;
        }
        temp = getch();
        temp -= 48;
        while (temp < 0 || temp > numberOfPlayers)
        {
            if(mode == 1)
                if(temp == 52 || temp == 20 || temp == 34 || temp == 66) break;
            clear_screen();
            printProfiles();
            change_color_rgb(255, 196, 0);
            cout << "Please choose a profile: " << endl;
            reset_color();
            for (int i = 0 , j = 0; i < 10; i++ , j++)
            {
                addr = "files/players/player";
                addr += (char)(i+48);
                addr += "/regStat.txt";
                file.open(addr , ios::in);
                file >> registeryStatus;
                file.close();
                if(registeryStatus == 1)
                {
                    addr = "files/players/player";
                    addr += (char)(i+48);
                    addr += "/name.txt";
                    file.open(addr , ios::in);
                    file >> name;
                    change_color_rgb(255 , 0 , 0);
                    cout << '[';
                    reset_color();
                    change_color_rgb(0 , 255 , 0);
                    cout << j;
                    reset_color();
                    change_color_rgb(255 , 0 , 0);
                    cout << "] ";
                    reset_color();
                    change_color_rgb(0 , 255 , 255);
                    cout << name;
                    reset_color();
                    cout << endl; 
                    file.close();
                }
                else j--;
            }
            if(numberOfPlayers < 10)
            {
                change_color_rgb(255 , 0 , 0);
                cout << '[';
                reset_color();
                change_color_rgb(0 , 255 , 0);
                cout << numberOfPlayers;
                reset_color();
                change_color_rgb(255 , 0 , 0);
                cout << "] ";
                reset_color();
                change_color_rgb(0 , 255 , 0);
                cout << "Create a new profile";
                reset_color();
                cout << endl;
            }
            if(mode == 1)
            {
                change_color_rgb(255 , 0 , 0);
                cout << '[';
                reset_color();
                change_color_rgb(255 , 255 , 0);
                cout << 'r';
                reset_color();
                change_color_rgb(255 , 0 , 0);
                cout << "] ";
                reset_color();
                change_color_rgb(255 , 255 , 0);
                cout << "Change Name";
                reset_color();
                cout << endl;

                change_color_rgb(255 , 0 , 0);
                cout << '[';
                reset_color();
                change_color_rgb(255,69,0);
                cout << 'd';
                reset_color();
                change_color_rgb(255, 0 , 0);
                cout << "] ";
                reset_color();
                change_color_rgb(255,69,0);
                cout << "Delete a profile";
                reset_color();
                cout << endl;
            }
            change_color_rgb(255 , 0 , 0);
            cout << endl << "Wrong input, please try again: " << endl;
            reset_color();
            temp = getch();
            temp -= 48;
        }
        if(temp != numberOfPlayers && numberOfPlayers != 10)
        {
            for (int i = 0; i < 10; i++)
            {
                addr = "files/players/player";
                addr += (char)(i+48);
                addr += "/regStat.txt";
                file.open(addr , ios::in);
                file >> registeryStatus;
                file.close();
                if(registeryStatus == 1)
                {
                    if(profileIterator == temp)
                    {
                        profileIterator = i;
                        break;
                    }
                    profileIterator++;
                }
            }
        }
        if(mode == 1)
        {
            if(temp == 52 || temp == 20)
            {
                deleteProfile();
                return;
            }
            else if(temp == 34 || temp == 66)
            {
                changeName();
                return;
            }
        }
        if(numberOfPlayers < 10)
        {
            if(temp < numberOfPlayers)
            {
                currentPlayer = "player";
                currentPlayer += (char)(profileIterator+48);
            }
            else
            {
                registerUser();
            }
        }
        else
        {
            currentPlayer = "player";
            currentPlayer += (char)(temp+48);
        }
    }
    mainMenu();
}

int findEmptyProfile()
{
    int temp;
    ifstream inFile;
    string addr;
    for (int i = 0; i < 10; i++)
    {
        addr = "files/players/player";
        addr += (char)(i+48);
        addr += "/regStat.txt";
        inFile.open(addr , ios::in);
        inFile >> temp;
        if(temp == 0)
        {
            return i;
        }
        inFile.close();
    }
    return -1;
}

void deleteProfile()
{
    clear_screen();
    ifstream file;
    string addr , name;
    int registeryStatus , temp , numberOfPlayers , profileIterator = 0;
    char deletingCurrentPlayerOption;
    int flag = 0; //this flag is for deleting current player.
    file.open("files/numberOfRegisteredPlayers.txt" , ios::in);
    file >> numberOfPlayers;
    file.close();
    change_color_rgb(255 , 0 , 0);
    cout << "Please choose a profile to delete:" << endl;
    reset_color();
    for (int i = 0 , j = 0; i < 10; i++ , j++)
    {
        addr = "files/players/player";
        addr += (char)(i+48);
        addr += "/regStat.txt";
        file.open(addr , ios::in);
        file >> registeryStatus;
        file.close();
        if(registeryStatus == 1)
        {
            addr = "files/players/player";
            addr += (char)(i+48);
            addr += "/name.txt";
            
            file.open(addr , ios::in);
            file >> name;
            
            change_color_rgb(255 , 0 , 0);
            cout << '[';
            reset_color();
            change_color_rgb(255, 0, 242);
            cout << j;
            reset_color();
            change_color_rgb(255 , 0 , 0);
            cout << "] ";
            reset_color();
            change_color_rgb(140, 255, 0);
            cout << name;
            reset_color();
            cout << endl;
             
            file.close();
        }
        else j--;
    }
    temp = getch();
    temp -= 48;
    while (temp < 0 || temp >= numberOfPlayers)
    {
        clear_screen();
        change_color_rgb(255 , 0 , 0);
        cout << "Please choose a profile to delete:" << endl;
        reset_color();
        for (int i = 0 , j = 0; i < 10; i++ , j++)
        {
            addr = "files/players/player";
            addr += (char)(i+48);
            addr += "/regStat.txt";
            file.open(addr , ios::in);
            file >> registeryStatus;
            file.close();
            if(registeryStatus == 1)
            {
                addr = "files/players/player";
                addr += (char)(i+48);
                addr += "/name.txt";

                file.open(addr , ios::in);
                file >> name;
                change_color_rgb(255 , 0 , 0);
                cout << '[';
                reset_color();
                change_color_rgb(255, 0, 242);
                cout << j;
                reset_color();
                change_color_rgb(255 , 0 , 0);
                cout << "] ";
                reset_color();
                change_color_rgb(140, 255, 0);
                cout << name;
                reset_color();
                cout << endl;
 
                file.close();
            }
            else j--;
        }
        change_color_rgb(255 , 0 ,0);
        cout << endl << "Wrong input, please try again: " << endl;
        reset_color();
        temp = getch();
        temp -= 48;
    }

    for (int i = 0; i < 10; i++)
    {
        addr = "files/players/player";
        addr += (char)(i+48);
        addr += "/regStat.txt";
        file.open(addr , ios::in);
        file >> registeryStatus;
        file.close();
        if(registeryStatus == 1)
        {
            if(profileIterator == temp)
            {
                profileIterator = i;
                break;
            }
            profileIterator++;
        }
    }

    if(profileIterator+48 == currentPlayer[6])
    {
        clear_screen();
        change_color_rgb(0 , 255 , 255);
        cout << " * ";
        reset_color();
        change_color_rgb(255 , 0 , 0);
        cout << "You are going to delete the current player!" << endl;
        reset_color();
        change_color_rgb(0 , 255 , 255);
        cout << " * ";
        reset_color();
        change_color_rgb(255, 166, 0);
        cout << "You have to choose another username after deleting this user" << endl;
        reset_color();
        change_color_rgb(0 , 255 , 255);
        cout << " * ";
        reset_color();
        change_color_rgb(255, 166, 0);
        cout << "Do you want to continue[y/n]: ";
        reset_color();
        deletingCurrentPlayerOption = getch();
        while (deletingCurrentPlayerOption != 'y' && deletingCurrentPlayerOption != 'Y' && deletingCurrentPlayerOption != 'n' && deletingCurrentPlayerOption != 'N')
        {
            clear_screen();
            change_color_rgb(0 , 255 , 255);
            cout << " * ";
            reset_color();
            change_color_rgb(255 , 0 , 0);
            cout << "You are going to delete the current player!" << endl;
            reset_color();
            change_color_rgb(0 , 255 , 255);
            cout << " * ";
            reset_color();
            change_color_rgb(255, 166, 0);
            cout << "You have to choose another username after deleting this user" << endl;
            reset_color();
            change_color_rgb(0 , 255 , 255);
            cout << " * ";
            reset_color();
            change_color_rgb(255, 166, 0);
            cout << "Wrong input, please try again[y/n]: " << endl;
            reset_color();
            deletingCurrentPlayerOption = getch();
        }
        if(deletingCurrentPlayerOption == 'y' || deletingCurrentPlayerOption == 'Y')
        {
            flag = 1;
        }
        else
        {
            choosingProfile(1);
        }
    }

    addr = "files/players/player";
    addr += (char)(profileIterator+48);
    ofstream outFile;
    outFile.open((addr + "/name.txt") , ios::out | ios::trunc);
    outFile << "";
    outFile.close();
    outFile.open((addr + "/numberOfFilledSlots.txt") , ios::out | ios::trunc);
    outFile << "";
    outFile.close();
    outFile.open((addr + "/regStat.txt") , ios::out | ios::trunc);
    outFile << '0';
    outFile.close();
    outFile.open((addr) + "/score.txt" , ios::out | ios::trunc);
    outFile << "";
    outFile.close();
    addr += "/slots";
    for (int i = 1; i <= 4; i++)
    {
        outFile.open((addr + "/slot" + (char)(i+48) + "/save.txt") , ios::out | ios::trunc);
        outFile << "0";
        outFile.close();
    }
    file.open("files/numberOfRegisteredPlayers.txt" , ios::in);
    file >> numberOfPlayers;
    file.close();
    outFile.open("files/numberOfRegisteredPlayers.txt" , ios::in | ios::trunc);
    outFile << numberOfPlayers-1;
    outFile.close();
    if(flag == 1)
        choosingProfile(0);
    else
    {
        mainMenu();
        return;
    }
}

int profileNameInputCheck(char* name)
{
    int length = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        length++;
        if(name[i] < 48) return 0;
        if(name[i] > 57 && name[i] < 65) return 0;
        if(name[i] > 90 && name[i] < 97) return 0;
        if(name[i] > 122) return 0;
    }
    if(length > 20 || length < 3) return 0;
    ifstream inFile;
    string mainPath = "files/players/player";
    int temp;
    string strName = name , playerNames;
    for (int i = 0; i < 10; i++)
    {
        inFile.open((mainPath + (char)(i+48) + "/regStat.txt") , ios::in);
        inFile >> temp;
        inFile.close();
        if(temp == 1)
        {
            inFile.open((mainPath + (char)(i+48) + "/name.txt") , ios::in);
            inFile >> playerNames;
            inFile.close();
            if(playerNames == strName)
                return -1;
        }
    }
    return 1;
}

void mainMenu()
{
    int temp;
    string name;
    ifstream inFile;
    clear_screen();

    printMineSweeper();
    printMainmenu();

    inFile.open(("files/players/" + currentPlayer + "/name.txt") , ios::in);
    inFile >> name;
    inFile.close();

    cout << endl;
    change_color_rgb(0,255,255);
    cout << "Current Player";
    reset_color();
    cout << ": ";
    change_color_rgb(255 ,0 ,0);
    cout << "* ";
    change_color_rgb(0,255,0);
    cout << name;
    change_color_rgb(255,0,0);
    cout << " *" << endl;
    reset_color();

    inFile.open(("files/players/" + currentPlayer + "/score.txt") , ios::in);
    inFile >> temp;
    inFile.close();

    change_color_rgb(0,255,255);
    cout << "Current Score";
    reset_color();
    cout << ": ";
    change_color_rgb(255 ,0 ,0);
    cout << "* ";
    change_color_rgb(0,255,0);
    cout << temp;
    change_color_rgb(255,0,0);
    cout << " *" << endl << endl;
    reset_color();

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '1';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "New Game";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '2';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Load Game";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '3';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Profiles Setting";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '4';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Leaderboard";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '5';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Help";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '6';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Quit";
    reset_color();
    cout << endl;

    temp = getch();
    temp -= 48;

    while (temp < 1 || temp > 6)
    {
    clear_screen();

    printMineSweeper();
    printMainmenu();

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '1';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "New Game";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '2';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Load Game";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '3';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Profiles Setting";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '4';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Leaderboard";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '5';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Help";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout << '[';
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '6';
    reset_color();
    change_color_rgb(255 , 0 , 0);
    cout << "] ";
    reset_color();
    change_color_rgb(0 , 255 , 255);
    cout << "Quit";
    reset_color();
    cout << endl;

    change_color_rgb(255 , 0 , 0);
    cout  << endl << "Wrong Input, Please Try Again: ";
    reset_color();

    temp = getch();
    temp -= 48;
    }

    switch (temp)
    {
    case 1:
        newGame();
        break;
    case 2:
        loadGame();
        break;
    case 3:
        choosingProfile(1);
        break;
    case 4:
        leaderBoard();
        break;
    case 5:
        help();
        break;
    case 6:
        clear_screen();
        exit(0);
        break;
    }
}

void printMainmenu()
{
    change_color_rgb(255, 0, 200);
    cout << "    __  ___      _          __  ___                " << endl <<
    "   /  |/  /___ _(_)___     /  |/  /__  ____  __  __" << endl <<
    "  / /|_/ / __ `/ / __ \\   / /|_/ / _ \\/ __ \\/ / / /" << endl << 
    " / /  / / /_/ / / / / /  / /  / /  __/ / / / /_/ / " << endl << 
    "/_/  /_/\\__,_/_/_/ /_/  /_/  /_/\\___/_/ /_/\\__,_/  " << endl;
    reset_color();
    cout << endl;
}

void printMineSweeper()
{
    change_color_rgb(255, 10, 67);
    cout << "    __  ____                                                   " << endl;
    cout << "   /  |/  (_)___  ___  ______      _____  ___  ____  ___  _____" << endl <<
    "  / /|_/ / / __ \\/ _ \\/ ___/ | /| / / _ \\/ _ \\/ __ \\/ _ \\/ ___/" << endl <<
    " / /  / / / / / /  __(__  )| |/ |/ /  __/  __/ /_/ /  __/ /    " << endl <<
    "/_/  /_/_/_/ /_/\\___/____/ |__/|__/\\___/\\___/ .___/\\___/_/     " << endl <<
    "                                           /_/                 " << endl;
    reset_color();
    cout << endl;
}

void customGame()
{
    int row , col , mine;

    clear_screen();
    change_color_rgb(0 , 255 , 0);
    cout << " * ";
    reset_color();
    change_color_rgb(255,69,0);
    cout << "Please enter the number of rows";
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '(';
    reset_color();
    change_color_rgb(0 , 255 ,255);
    cout << "Between 5 & 20";
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << ')';
    reset_color();
    cout << ':' << endl;
    cin >> row;

    while (!RCMCheck(row , 5 , 20))
    {
        clear_screen();
        change_color_rgb(0 , 255 , 0);
        cout << " * ";
        reset_color();
        change_color_rgb(255,69,0);
        cout << "Please enter the number of rows";
        reset_color();
        change_color_rgb(0 , 255 , 0);
        cout << '(';
        reset_color();
        change_color_rgb(0 , 255 ,255);
        cout << "Between 5 & 20";
        reset_color();
        change_color_rgb(0 , 255 , 0);
        cout << ')';
        reset_color();
        cout << endl;
        change_color_rgb(0 , 255 , 0);
        cout << " * ";
        reset_color();
        change_color_rgb(255 , 0 , 0);
        cout << "The Amount Is Not Allowed, Please Try Again: ";
        reset_color();
        cin >> row;
    }

    clear_screen();
    change_color_rgb(0 , 255 , 0);
    cout << " * ";
    reset_color();
    change_color_rgb(255,69,0);
    cout << "Please enter the number of cols";
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '(';
    reset_color();
    change_color_rgb(0 , 255 ,255);
    cout << "Between 5 & 20";
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << ')';
    reset_color();
    cout << ':' << endl;
    cin >> col;

    while (!RCMCheck(col , 5 , 20))
    {
        clear_screen();
        change_color_rgb(0 , 255 , 0);
        cout << " * ";
        reset_color();
        change_color_rgb(255,69,0);
        cout << "Please enter the number of cols";
        reset_color();
        change_color_rgb(0 , 255 , 0);
        cout << '(';
        reset_color();
        change_color_rgb(0 , 255 ,255);
        cout << "Between 5 & 20";
        reset_color();
        change_color_rgb(0 , 255 , 0);
        cout << ')';
        reset_color();
        cout << endl;
        change_color_rgb(0 , 255 , 0);
        cout << " * ";
        reset_color();
        change_color_rgb(255 , 0 , 0);
        cout << "The Amount Is Not Allowed, Please Try Again: ";
        reset_color();
        cin >> col;
    }
    
    clear_screen();
    change_color_rgb(0 , 255 , 0);
    cout << " * ";
    reset_color();
    change_color_rgb(255,69,0);
    cout << "Please enter the number of mines";
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << '(';
    reset_color();
    change_color_rgb(0 , 255 ,255);
    cout << "Between 4 & " << col*row-1;
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << ')';
    reset_color();
    cout << ':' << endl;
    cin >> mine;

    while (!RCMCheck(mine , 4 , row*col-1))
    {
        clear_screen();
        change_color_rgb(0 , 255 , 0);
        cout << " * ";
        reset_color();
        change_color_rgb(255,69,0);
        cout << "Please enter the number of mines";
        reset_color();
        change_color_rgb(0 , 255 , 0);
        cout << '(';
        reset_color();
        change_color_rgb(0 , 255 ,255);
        cout << "Between 4 &" << col*row-1;
        reset_color();
        change_color_rgb(0 , 255 , 0);
        cout << ')';
        reset_color();
        cout << endl;
        change_color_rgb(0 , 255 , 0);
        cout << " * ";
        reset_color();
        change_color_rgb(255 , 0 , 0);
        cout << "The Amount Is Not Allowed, Please Try Again: ";
        reset_color();
        cin >> mine;
    }
    height = row;
    width = col;
    numberOfBombs = mine;
}

bool RCMCheck(int input , int a , int b) // A function for checking rows and columns and mines of custom game;
{
    if(input > b || input < a) return false;
    return true;
}

void creatingGameBoardAndMines()
{
    numberOfCloseSafeHouses = height*width - numberOfBombs;
    numberOfRemainingFlags = numberOfBombs;
    matchScore = (width * height * 5) + (numberOfBombs * 10);

    homesPrintMode = new int*[height];
    bombs = new int*[height];
    aroundBombsCount = new int*[height];
    for (int i = 0; i < height; i++)
    {
        homesPrintMode[i] = new int[width];
        bombs[i] = new int[width];
        aroundBombsCount[i] = new int[width];
    }

    assignBomb();
    setFirstPrintState();
    checkAroundBombs();
}

void leaderBoard()
{
    clear_screen();
    ifstream inFile;
    int n , temp;
    inFile.open("files/numberOfRegisteredPlayers.txt" , ios::in);
    inFile >> n;
    inFile.close();
    string mainPath = "files/players/player";
    string* players = new string[n];
    int* scores = new int[n];
    for (int i = 0 , j = 0; i < 10; i++)
    {
        inFile.open((mainPath + (char)(i+48) + "/regStat.txt") , ios::in);
        inFile >> temp;
        inFile.close();
        if(temp == 1)
        {
            inFile.open((mainPath + (char)(i+48) + "/name.txt") , ios::in);
            inFile >> players[j];
            inFile.close();
            inFile.open((mainPath + (char)(i+48) + "/score.txt") , ios::in);
            inFile >> scores[j];
            inFile.close();
            j++;
        }
    }

    for (int i = 0; i < n-1; i++)     
    {
        for (int j = 0; j < n-i-1; j++)
        { 
            if (scores[j] < scores[j+1])
            { 
                swap(&scores[j], &scores[j+1]);
                swap(&players[j], &players[j+1]);
            } 
        }
    }
    printLeaderBoard();
    change_color_rgb(0,255,0);
    cout << " * ";
    reset_color();
    change_color_rgb(255, 5, 147);
    cout << "Leader Board";
    reset_color();
    change_color_rgb(0 , 255 , 0);
    cout << " * ";
    reset_color(); cout << endl;
    change_color_rgb(0 , 255 , 255);
    cout << "Players";
    reset_color();
    cout << "\t\t";
    change_color_rgb(0 , 255 , 0);
    cout << "Scores";
    reset_color();
    cout << endl;
    cout << "-----------------------";
    cout << endl;


    if(n < 5)
    {
        for (int i = 0; i < n; i++)
        {
            change_color_rgb(0 , 255 , 255);
            cout << players[i] << "\t\t";
            reset_color();
            change_color_rgb(0 , 255 , 0);
            cout << scores[i] << endl;
            reset_color();
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            cout << players[i] << '\t' << scores[i] << endl;
        }
    }

    delete[] scores;
    delete[] players;

    cout << endl << "Press any key to continue..." << endl;
    getch();

    mainMenu();
}

void swap(int *a, int *b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void swap(string *a, string *b) 
{ 
    string temp = *a; 
    *a = *b; 
    *b = temp; 
} 

void changeName()
{
    clear_screen();
    ifstream inFile;
    string mainPath = "files/players/" , tempStr;
    char nameStr[100];
    inFile.open((mainPath + currentPlayer + "/name.txt") , ios::in);
    inFile >> nameStr;
    inFile.close();
    change_color_rgb(0,255,0);
    cout << " * ";
    change_color_rgb( 255 , 255 , 0);
    cout << "The name of the current profile is ";
    reset_color();
    cout << "\"";
    change_color_rgb(0,255 , 255);
    cout << nameStr;
    reset_color();
    cout << '\"';
    cout << endl;
    change_color_rgb(0,255,0);
    cout << " * ";
    change_color_rgb(255 , 0 , 255);
    cout << "Please enter a new name for this profile" << endl;
    change_color_rgb(0,255,0);
    cout << " * ";
    change_color_rgb(255, 165, 0);
    cout << "You can type \"e\" or \"E\" and then press [Enter] to return to profile menu: ";
    reset_color();
    cin.getline(nameStr , 100);
    tempStr = nameStr;
    if(tempStr == "e" || tempStr == "E") {
        choosingProfile(1);
        return;
    }
    while (profileNameInputCheck(nameStr) != 1)
    {
        clear_screen();
        if(profileNameInputCheck(nameStr) == 0)
        {
            change_color_rgb(255 , 0 , 0);
            cout << "Wrong input please try again" << endl;
            reset_color();
        }
        else if(profileNameInputCheck(nameStr) == -1)
        {
            change_color_rgb(255 , 0 , 0);
            cout << "This username exists , Please choose another one" << endl;
            reset_color();
        }
        cout << "You can type \"e\" or \"E\" and then press [Enter] to back to profile menu: ";
        cin.getline(nameStr , 100);
        tempStr = nameStr;
        if(tempStr == "e" || tempStr == "E") {
        choosingProfile(1);
        return;
    }
    }
    ofstream outFile;
    outFile.open((mainPath + currentPlayer + "/name.txt") , ios::out | ios::trunc);
    outFile << nameStr;
    outFile.close();
    mainMenu();
}

void help()
{
    clear_screen();
    printHelp();
    cout << "Print any key to return to main menu...." << endl;
    getch();
    mainMenu();
    return;
}

void newGame()
{
    char temp;
    clear_screen();
    printNewGame();
    change_color_rgb(0,255,0);
    cout << " * ";
    reset_color();
    change_color_rgb(0,255,255);
    cout << "Please choose a gamemode: " << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '1';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(0,255,0);
    cout << "Easy: 5 By 5 With 4 Mines" << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '2';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(255, 151, 5);
    cout << "Normal: 12 By 12 With 28 Mines" << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '3';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(255,0,0);
    cout << "Hard: 20 By 20 With 96 Mines" << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '4';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(0,255,0);
    cout << "Custom" << endl;
    reset_color();

    temp = getch();

    while (temp < 49 || temp > 52)
    {
    clear_screen();
    printNewGame();
    change_color_rgb(0,255,0);
    cout << " * ";
    reset_color();
    change_color_rgb(0,255,255);
    cout << "Please choose a gamemode: " << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '1';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(0,255,0);
    cout << "Easy: 5 By 5 With 4 Mines" << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '2';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(255, 151, 5);
    cout << "Normal: 12 By 12 With 28 Mines" << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '3';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(255,0,0);
    cout << "Hard: 20 By 20 With 96 Mines" << endl << endl;
    reset_color();

    change_color_rgb(255,0,0);
    cout << '[';
    reset_color();
    change_color_rgb(0,255,0);
    cout << '4';
    reset_color();
    change_color_rgb(255,0,0);
    cout << "] ";
    reset_color();
    change_color_rgb(0,255,0);
    cout << "Custom" << endl;
    reset_color();

    change_color_rgb(255, 0 , 0);
    cout << "Wrong Input, Please Try Again: ";
    reset_color();
    temp = getch();
    }
    
    if(height != 0)
    {
        for (int i = 0; i < height; i++)
        {
            delete[] homesPrintMode[i];
            delete[] bombs[i];
            delete[]aroundBombsCount[i];
        }
        delete[] homesPrintMode;
        delete[] bombs;
        delete[] aroundBombsCount;
    }

    switch (temp)
    {
    case '1':
        height = 5;
        width = 5;
        numberOfBombs = 4;
        break;
    case '2':
        height = 12;
        width = 12;
        numberOfBombs = 28;
        break;
    case '3':
        height = 20;
        width = 20;
        numberOfBombs = 96;
        break;
    case '4':
        customGame();
        break;
    }
    currentSave = 0;
    creatingGameBoardAndMines();
    loading();
    game();
}

void openAroundSafeHouses(int i , int j)
{
    //i = (y - 2) / 2;
    //j = (x - 3) / 4;

    if (i - 1 >= 0)
    {
        if (j - 1 >= 0)
        {
            if (bombs[i - 1][j - 1] == 0)
            {
                if(homesPrintMode[i-1][j-1] == 0)
                {
                    homesPrintMode[i-1][j-1] = 1;
                    numberOfCloseSafeHouses--;
                    if(aroundBombsCount[i-1][j-1] == 0)
                    {
                        openAroundSafeHouses(i-1 , j-1);
                    }
                }
            }
        }
        if (j + 1 < height)
        {
            if (bombs[i - 1][j + 1] == 0)
            {
                if(homesPrintMode[i-1][j+1] == 0)
                {
                    homesPrintMode[i-1][j+1] = 1;
                    numberOfCloseSafeHouses--;
                    if(aroundBombsCount[i-1][j+1] == 0)
                    {
                        openAroundSafeHouses(i-1 , j+1);
                    }
                }
            }
        }
        if (bombs[i - 1][j] == 0)
        {
            if(homesPrintMode[i-1][j] == 0)
            {
                homesPrintMode[i-1][j] = 1;
                numberOfCloseSafeHouses--;
                if(aroundBombsCount[i-1][j] == 0)
                {
                    openAroundSafeHouses(i-1 , j);
                }
            }
        }
    }
    if (i + 1 < width)
    {
        if (j - 1 >= 0)
        {
            if (bombs[i + 1][j - 1] == 0)
            {
                if(homesPrintMode[i+1][j-1] == 0)
                {
                    homesPrintMode[i+1][j-1] = 1;
                    numberOfCloseSafeHouses--;
                    if(aroundBombsCount[i+1][j-1] == 0)
                    {
                        openAroundSafeHouses(i+1 , j-1);
                    }
                }
            }
        }
        if (j + 1 < height)
        {
            if (bombs[i + 1][j + 1] == 0)
            {
                if(homesPrintMode[i+1][j+1] == 0)
                {
                    homesPrintMode[i+1][j+1] = 1;
                    numberOfCloseSafeHouses--;
                    if(aroundBombsCount[i+1][j+1] == 0)
                    {
                        openAroundSafeHouses(i+1 , j+1);
                    }
                }
            }
        }
        if (bombs[i + 1][j] == 0)
        {
            if(homesPrintMode[i+1][j] == 0)
            {
                homesPrintMode[i+1][j] = 1;
                numberOfCloseSafeHouses--;
                if(aroundBombsCount[i+1][j] == 0)
                {
                    openAroundSafeHouses(i+1 , j);
                }
            }
        }
    }
    if (j - 1 >= 0)
    {
        if (bombs[i][j - 1] == 0)
        {
            if(homesPrintMode[i][j-1] == 0)
            {
                homesPrintMode[i][j-1] = 1;
                numberOfCloseSafeHouses--;
                if(aroundBombsCount[i][j-1] == 0)
                {
                    openAroundSafeHouses(i , j-1);
                }
            }
        }
    }
    if (j + 1 < height)
    {
        if (bombs[i][j + 1] == 0)
        {
            if(homesPrintMode[i][j+1] == 0)
            {
                homesPrintMode[i][j+1] = 1;
                numberOfCloseSafeHouses--;
                if(aroundBombsCount[i][j+1] == 0)
                {
                    openAroundSafeHouses(i , j+1);
                }
            }
        }
    }
}

void game()
{
    clear_screen();
    x = 3 ; y = 2;
    printBoard();
    cursor_to_pos(2 , 3);
    while (numberOfCloseSafeHouses > 0)
    {
        getInput();
        printBoard();
        cursor_to_pos(y ,x);
    }
    playerWon();
}

void playerLose()
{
    ofstream outFile;
    ifstream inFile;
    int temp;
    gameState = -1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(bombs[i][j] == 0)
                homesPrintMode[i][j] = 1;
            else
                homesPrintMode[i][j] = 2;
        }
    }
    printBoard();
    cout << endl;
    printYouLose();
    gameState = 0;
    if(currentSave != 0)
    {
        inFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::in);
        inFile >> temp;
        inFile.close();
        outFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::out | ios::trunc);
        outFile << temp-1;
        outFile.close();
        outFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(currentSave+48) + "/save.txt") , ios::out | ios::trunc);
        outFile << 0;
        outFile.close();
    }
    cout << endl << "Press any key to return To main menu...." << endl;
    getch();
    mainMenu();
}

void playerWon()
{
    ofstream outFile;
    ifstream inFile;
    int temp;
    gameState = 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(bombs[i][j] == 0)
                homesPrintMode[i][j] = 1;
            else
                homesPrintMode[i][j] = 2;
        }
    }
    printBoard();
    printYouWon();
    inFile.open(("files/players/" + currentPlayer + "/score.txt") , ios::in);
    inFile >> temp;
    inFile.close();
    temp += matchScore;
    outFile.open(("files/players/" + currentPlayer + "/score.txt") , ios::out | ios::trunc);
    outFile << temp;
    outFile.close();
    change_color_rgb(0,255,255);
    cout << "You earned: " << endl;
    change_color_rgb(0,255,0);
    cout << matchScore << endl;
    change_color_rgb(0,255,255);
    cout << "Your Current Score: " << endl;
    change_color_rgb(0,255,0);
    cout << temp << endl;
    reset_color();

    gameState = 0;
    if(currentSave != 0)
    {
        inFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::in);
        inFile >> temp;
        inFile.close();
        outFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::out | ios::trunc);
        outFile << temp-1;
        outFile.close();
        outFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(currentSave+48) + "/save.txt") , ios::out | ios::trunc);
        outFile << 0;
        outFile.close();
    }
    cout << endl << "Press any key to return to main menu...." << endl;
    getch();
    mainMenu();
}

void printYouWon()
{
    change_color_rgb(0,255,0);
    cout << "__  __               _       __          " <<endl;
    cout << "\\ \\/ /___  __  __   | |     / /___  ____ " << endl;
    cout << " \\  / __ \\/ / / /   | | /| / / __ \\/ __ \\" << endl;
    cout << " / / /_/ / /_/ /    | |/ |/ / /_/ / / / /" << endl;
    cout << "/_/\\____/\\__,_/     |__/|__/\\____/_/ /_/ " << endl;
    reset_color();
    cout << endl;
}

void printYouLose()
{
    change_color_rgb(255,0,0);
    cout << "__  __               __                    __" << endl;
    cout << "\\ \\/ /___  __  __   / /   ____  ________  / /" << endl;
    cout << " \\  / __ \\/ / / /  / /   / __ \\/ ___/ _ \\/ / " << endl;
    cout << " / / /_/ / /_/ /  / /___/ /_/ (__  )  __/_/  " << endl;
    cout << "/_/\\____/\\__,_/  /_____/\\____/____/\\___(_)   " << endl;
    reset_color();
    cout << endl;
}

void pauseMenu()
{
    char ch;
    clear_screen();
    printPauseMenu();
    change_color_rgb(0,255,0);
    cout << "[1]Resume" << endl;
    change_color_rgb(234, 240, 72);
    cout << "[2]Save" << endl;
    change_color_rgb(255,69,0);
    cout << "[3]Main Menu" << endl;
    change_color_rgb(255 , 0 , 0);
    cout << "[4]Exit" << endl;
    reset_color();
    ch = getch();
    while(ch > 52 || ch < 49)
    {
        clear_screen();
        printPauseMenu();
        change_color_rgb(0,255,0);
        cout << "[1]Resume" << endl;
        change_color_rgb(234, 240, 72);
        cout << "[2]Save" << endl;
        change_color_rgb(255,69,0);
        cout << "[3]Main Menu" << endl;
        change_color_rgb(255 , 0 , 0);
        cout << "[4]Exit" << endl;
        cout << "Invalid Input! Please Try Again: " << endl;
        reset_color();
        ch = getch();
    }
    switch (ch)
    {
        case '1':
            return;
            break;
        case '2':
            saveGame();
            break;
        case '3':
            mainMenu();
            break;
        case '4':
        clear_screen();
            exit(0);
            break;
    }
}

void printPauseMenu()
{
    change_color_rgb(10, 239, 255);
    cout << 
    "    ____                           __  ___                " << endl <<
    "   / __ \\____ ___  __________     /  |/  /__  ____  __  __" << endl <<
    "  / /_/ / __ `/ / / / ___/ _ \\   / /|_/ / _ \\/ __ \\/ / / /" << endl <<
    " / ____/ /_/ / /_/ (__  )  __/  / /  / /  __/ / / / /_/ / " << endl << 
    "/_/    \\__,_/\\__,_/____/\\___/  /_/  /_/\\___/_/ /_/\\__,_/  " << endl;
    reset_color();
    cout << endl;
}

void saveGame()
{
    clear_screen();
    int nslots , temp;
    char input;
    string slotName;
    ifstream inFile;
    inFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::in);
    inFile >> nslots;
    inFile.close();
    change_color_rgb(0,255,0);
    cout << " * ";
    change_color_rgb(0, 255 , 255);
    cout << "Please choose a slot: " << endl;
    reset_color();
    for (int i = 0 , j = 1; i < 4; i++)
    {
        inFile.open(("files/players/" + currentPlayer + "/slots/slot" + char(i+49) + "/save.txt") , ios::in);
        inFile >> temp;
        if(temp == 1)
        {
            inFile >> slotName;
            change_color_rgb(255, 0 , 0 );
            cout << '[';
            change_color_rgb(0,255,0);
            cout << j;
            change_color_rgb(255, 0 , 0);
            cout << "] ";
            change_color_rgb(0,255,255);
            cout << slotName << endl;
            reset_color();
            j++;
        }
        inFile.close();
    }
    if(nslots < 4)
    {
        change_color_rgb(255,0,0);
        cout << '[';
        change_color_rgb(0,255,0);
        cout << 'n';
        change_color_rgb(255,0,0);
        cout << "] ";
        change_color_rgb(0,255,0);
        cout << "Create a new slot" << endl;
        reset_color();
    }
    if(nslots != 0)
    {
        change_color_rgb(255,0,0);
        cout << '[';
        change_color_rgb(0,255,0);
        cout << 'd';
        change_color_rgb(255,0,0);
        cout << "] ";
        change_color_rgb(255 , 0 , 0);
        cout << "Delete a slot" << endl;
        reset_color();
    }
    change_color_rgb(255,0,0);
    cout << '[';
    change_color_rgb(0,255,0);
    cout << 'c';
    change_color_rgb(255,0,0);
    cout << "] ";
    change_color_rgb(255 , 255 , 0);
    cout << "Cancell";
    reset_color();
    input = getch();
    while (input < '1' || input > (nslots+48))
    {
        if(input == 'c' || input == 'C' || input == 'n' || input == 'N') break;
        if(nslots != 0)
        {
            if (input == 'd' || input == 'D')
                break;
        }
        input = getch();
    }
    if(input == 'c' || input == 'C') return;
    if(input == 'd' || input == 'D')
    {
        deleteSaveSlot(nslots);
        return;
    }
    input -= 48;
    string addr;
    int slotIterator = 1;
    for (int i = 1; i < 5; i++)
    {
        addr = "files/players/";
        addr += currentPlayer;
        addr += "/slots/slot";
        addr += char(i+48);
        addr += "/save.txt";
        inFile.open(addr , ios::in);
        inFile >> temp;
        inFile.close();
        if(temp == 1)
        {
            if(slotIterator == input)
            {
                slotIterator = i;
                break;
            }
            slotIterator++;
        }
    }
    if(input == 'n'-48 || input == 'N'-48)
    {
        slotIterator = createSaveSlot(nslots);
    }
    clear_screen();
    ofstream outFile;
    outFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(slotIterator+48) + "/save.txt") , ios::out | ios::trunc);
    outFile << 1 << endl;
    char name[100];
    change_color_rgb(0,255,0);
    cout << " * ";
    change_color_rgb(0,255,255);
    cout << " Please enter a name for save slot: ";
    reset_color();
    cin.getline(name , 100);
    while (saveSlotNameCheck(name , slotIterator) != 1)
    {
        clear_screen();
        change_color_rgb(0,255,0);
        cout << " * ";
        change_color_rgb(0,255,255);
        if(saveSlotNameCheck(name , slotIterator) == 0)
            cout << "Invalid input, please try again: ";
        else if(saveSlotNameCheck(name , slotIterator) == -1)
            cout << "This name has been used before, please try again: ";
            reset_color();
        cin.getline(name , 100);
    }
    outFile << name << endl;
    outFile << height << endl;
    outFile << width << endl;
    outFile << numberOfBombs << endl;
    outFile << numberOfCloseSafeHouses << endl;
    outFile << numberOfRemainingFlags << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outFile << bombs[i][j] << ' ';
        }
        outFile << endl;
    }
    outFile << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outFile << homesPrintMode[i][j] << ' ';
        }
        outFile << endl;
    }
    outFile << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outFile << aroundBombsCount[i][j] << ' ';
        }
        outFile << endl;
    }
    outFile.close();
}

int createSaveSlot(int nslots)
{
    clear_screen();
    int temp;
    ifstream inFile;
    for (int i = 1; i < 5; i++)
    {
        inFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(i+48) + "/save.txt") , ios::in);
        inFile >> temp;
        if(temp == 0)
        {
            temp = i;
            inFile.close();
            break;
        }
        inFile.close();
    }
    ofstream outFile;
    outFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(temp+48) + "/save.txt") , ios::in | ios::trunc);
    outFile << 1 << endl;
    outFile.close();
    outFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::out | ios::trunc);
    outFile << nslots+1;
    outFile.close();
    return temp;
}

void deleteSaveSlot(int nslots)
{
    clear_screen();
    int temp , input;
    string slotName;
    ifstream inFile;
    change_color_rgb(0 , 255 , 0);
    cout << " * ";
    change_color_rgb(0 , 255 , 255);
    cout << "Please choose a slot to delete: " << endl;
    reset_color();
    for (int i = 1 , j = 1; i < 5; i++)
    {
        inFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(i+48) + "/save.txt") , ios::in);
        inFile >> temp;
        if(temp == 1)
        {
            inFile >> slotName;
            change_color_rgb(255,0,0);
            cout << '[';
            change_color_rgb(0,255,0);
            cout << j;
            change_color_rgb(255, 0 , 0);
            cout << "] ";
            change_color_rgb(0 , 255 , 255);
            cout << slotName << endl;
            reset_color();
            inFile.close();
            j++;
        }
        else inFile.close();
    }
    input = getch();
    input -= 48;
    while (input < 1 || input > nslots)
    {
        input = getch();
        input -= 48;
    }
    
    int slotIterator = 1;
    for (int i = 1; i < 5; i++)
    {
        inFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(i+48) + "/save.txt") , ios::in);
        inFile >> temp;
        inFile.close();
        if(temp == 1)
        {
            if(slotIterator == input)
            {
                slotIterator = i;
                break;
            }
            slotIterator++;
        }
    }

    ofstream outFile;
    outFile.open(("files/players/" + currentPlayer + "/slots/slot" + char(slotIterator+48) + "/save.txt") , ios::out | ios::trunc);
    outFile << 0;
    outFile.close();
    outFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::out | ios::trunc);
    outFile << nslots-1;
    outFile.close();
}

void loadGame()
{
    clear_screen();
    int nslots , temp;
    char input;
    string slotName , tempStr;
    ifstream inFile;
    inFile.open(("files/players/" + currentPlayer + "/numberOfFilledSlots.txt") , ios::in);
    inFile >> nslots;
    inFile.close();
    change_color_rgb(0,255,0);
    cout << " * ";
    change_color_rgb(0 , 255 , 255);
    cout << "Please choose a save slot: " << endl;
    reset_color();
    for (int i = 0 , j = 1; i < 4; i++)
    {
        inFile.open(("files/players/" + currentPlayer + "/slots/slot" + char(i+49) + "/save.txt") , ios::in);
        inFile >> temp;
        if(temp == 1)
        {
            inFile >> slotName;
            change_color_rgb(255,0,0);
            cout << '[';
            change_color_rgb(0 , 255 , 0);
            cout << j;
            change_color_rgb(255,0,0);
            cout << "] ";
            change_color_rgb(0 , 255 , 255);
            cout << slotName << endl;
            reset_color();
            j++;
        }
        inFile.close();
    }
    change_color_rgb(255,0,0);
    cout << '[';
    change_color_rgb(0,255,0);
    cout << 'c';
    change_color_rgb(255,0,0);
    cout << "] ";
    change_color_rgb(0,255,255);
    cout << "Cancell" << endl;
    reset_color();
    input = getch();
    while (input < '1' || input > (nslots+48))
    {
        if(input == 'c' || input == 'C') break;
        input = getch();
    }
    if(input == 'c') mainMenu();
    input -= 48;
    string addr;
    int slotIterator = 1;
    for (int i = 1; i < 5; i++)
    {
        addr = "files/players/";
        addr += currentPlayer;
        addr += "/slots/slot";
        addr += char(i+48);
        addr += "/save.txt";
        inFile.open(addr , ios::in);
        inFile >> temp;
        inFile.close();
        if(temp == 1)
        {
            if(slotIterator == input)
            {
                slotIterator = i;
                break;
            }
            slotIterator++;
        }
    }
    currentSave = slotIterator;
    if(height != 0)
    {
        for (int i = 0; i < height; i++)
        {
            delete[] homesPrintMode[i];
            delete[] bombs[i];
            delete[]aroundBombsCount[i];
        }
        delete[] homesPrintMode;
        delete[] bombs;
        delete[] aroundBombsCount;
    }
    inFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(slotIterator+48) + "/save.txt"));
    inFile >> temp;inFile >> tempStr;
    inFile >> height;
    inFile >> width;
    inFile >> numberOfBombs;
    inFile >> numberOfCloseSafeHouses;
    inFile >> numberOfRemainingFlags;

    bombs = new int*[height];
    homesPrintMode = new int*[height];
    aroundBombsCount = new int*[height];
    for (int i = 0; i < height; i++)
    {
        bombs[i] = new int[width];
        homesPrintMode[i] = new int[width];
        aroundBombsCount[i] = new int[width];
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            inFile >> bombs[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            inFile >> homesPrintMode[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            inFile >> aroundBombsCount[i][j];
        }
    }
    loading();
    game();
}

int saveSlotNameCheck(char* name , int n)
{
    int length = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        length++;
        if(name[i] < 48) return 0;
        if(name[i] > 57 && name[i] < 65) return 0;
        if(name[i] > 90 && name[i] < 97) return 0;
        if(name[i] > 122) return 0;
    }
    if(length > 15 || length < 1) return 0;
    ifstream inFile;
    string tempStr , strName = name;
    for (int i = 1; i < 5; i++)
    {
        if (i == n) continue;
        inFile.open(("files/players/" + currentPlayer + "/slots/slot" + (char)(i+48) + "/save.txt") , ios::in);
        inFile >> tempStr;
        if(tempStr == "1")
        {
            inFile >> tempStr;
            if (tempStr == strName)
            {
                inFile.close();
                return -1;
            }
        }
        inFile.close();
    }
    return 1;
}

void loading()
{
    clear_screen();
    printLoading();
    cout << endl;
    cout << "Loading:[" ;
    change_color_rgb(255,0,0);
    cout << "............................";
    reset_color();
    cout << "]";
    flush();
    cursor_to_pos(8 , 10);
    change_color_rgb(0,255,0);
    for (int i = 0; i < 5; i++)
    {
        flush();
        cout << "#";
        delay(300);
    }
    flush();
    delay(400);
    cout << "########";
    flush();
    delay(800);
    cout << "####";
    flush();
    delay(500);
    cout << "##";
    flush();
    for (int i = 0; i < 9; i++)
    {
        flush();
        cout << "#";
        delay(80);
    }
    cout << endl;
    flush();
    delay(200);
    clear_screen();
}

void printLoading()
{
    change_color_rgb(10, 255, 39);
    cout <<
    "    __                    ___            " << endl <<
    "   / /   ____  ____ _____/ (_)___  ____ _" << endl <<
    "  / /   / __ \\/ __ `/ __  / / __ \\/ __ `/" << endl <<
    " / /___/ /_/ / /_/ / /_/ / / / / / /_/ / " << endl <<
    "/_____/\\____/\\__,_/\\__,_/_/_/ /_/\\__, /  " << endl <<
    "                                /____/   " << endl;
    reset_color();
}

void printHelp()
{
    change_color_rgb(0, 0, 255);
    cout <<
    "    __  __     __    " << endl <<
    "   / / / /__  / /___ " << endl <<
    "  / /_/ / _ \\/ / __ \\" << endl <<
    " / __  /  __/ / /_/ /" << endl <<
    "/_/ /_/\\___/_/ .___/ " << endl <<
    "            /_/      " << endl;
    reset_color();
    cout << endl;
}

void printLeaderBoard()
{
    change_color_rgb(255, 5, 147);
    cout << 
    "    __                   __          __                         __" << endl <<
    "   / /   ___  ____ _____/ /__  _____/ /_  ____  ____ __________/ /" << endl <<
    "  / /   / _ \\/ __ `/ __  / _ \\/ ___/ __ \\/ __ \\/ __ `/ ___/ __  / " << endl <<
    " / /___/  __/ /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ / /  / /_/ /  " << endl <<
    "/_____/\\___/\\__,_/\\__,_/\\___/_/  /_.___/\\____/\\__,_/_/   \\__,_/   " << endl;
    reset_color();
    cout << endl; 
}

void printProfiles()
{
    change_color_rgb(255 , 255 , 0);
    cout << 
    "    ____             _____ __         " << endl << 
    "   / __ \\_________  / __(_) /__  _____" << endl <<
    "  / /_/ / ___/ __ \\/ /_/ / / _ \\/ ___/" << endl <<
    " / ____/ /  / /_/ / __/ / /  __(__  ) " << endl <<
    "/_/   /_/   \\____/_/ /_/_/\\___/____/ " << endl;
    reset_color();
    cout << endl;
}

void printNewGame()
{
    change_color_rgb(0,255,0);
    cout << 
    "    _   __                ______                   " << endl <<
    "   / | / /__ _      __   / ____/___ _____ ___  ___ " << endl <<
    "  /  |/ / _ \\ | /| / /  / / __/ __ `/ __ `__ \\/ _ \\" << endl <<
    " / /|  /  __/ |/ |/ /  / /_/ / /_/ / / / / / /  __/" << endl <<
    "/_/ |_/\\___/|__/|__/   \\____/\\__,_/_/ /_/ /_/\\___/ " << endl;
    reset_color();
    cout << endl;
}