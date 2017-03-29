#ifndef SERIAL_SEND
#define SERIAL_SEND

#include"SerialClass.h"
#include <tchar.h>
#include <time.h>
#define MAXAMMO 10
#define LIFE 10

class Cube
{
    protected:
    //Stores the bytes which will be printed
    unsigned char rawData[16] = {0};
    //Stores the cube next state
    bool cubeToPrint[5][5][5] = {{{0}}};
    //Stores the shoots for player 1
    bool shootMatrix1[5][5][5] = {{{0}}};
    //Stores the shoots for player 2
    bool shootMatrix2[5][5][5] = {{{0}}};
    //Pointer to the created handle
    Serial *SP;
    //Players life
    int Life1;
    int Life2;
    //Players ammo related variables
    bool AmmoChange;
    int Ammo1;
    int Ammo2;
    //Players positions
    int posPlayer1 = 12;
    int posPlayer2 = 12;
    public:
    //Constructor
    Cube (Serial *SPenter);
    //Prints the header
    void printHeader();
    //Begins connection
    int Begin();
    //Starts the game
    void Start();
    //Ends the game by printing the final message
    void End(int Winner);
    //Prints GET READY!
    void GetReady();
    //Prints the GAME OVER message
    void GameOver(int winner);
    //Prints the game menu and shows the options
    int Menu();
    //Controls the game scoreboard
    int GameControl();
    //Prints the life
    void PrintLife();
    //Prints the score
    int PrintScore();
    //Makes a player go up
    void PlayerGoUp(int play);
    //Makes a player go down
    void PlayerGoDown(int play);
    //Makes the player go left
    void PlayerGoLeft(int play);
    //Makes the player go right
    void PlayerGoRight(int play);
    //Makes the player shoot
    void PlayerShoot(int play);
    //Returns time difference
    long timediff(clock_t t1, clock_t t2);
    //Sends a string o bytes
    bool Write(unsigned char* toWrite, int messageSize);
    //Change a bit in cube next state array (returns 1 if succes)
    bool setPosition(int x, int y, int z, bool isOn);
    //Gets a position in the cube matrix
    bool getPosition(int x, int y, int z);
    //Prints the initial animation
    void initAnim();
    //Prints the menu animation
    void menuAnim();
    //Shows the animation of the player being destroyed
    void PlayerShot(int x, int y, int z);
    //Clears the cube
    void Clear();
    //Writes the player into the faces
    void WritePlayers();
    //Prints both shoot matrix into the cube itself
    void PrintMatrixShoot();
    //Writes into the actual cube (returns 1 if success)
    bool Print();
};

#endif
