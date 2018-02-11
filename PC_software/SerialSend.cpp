#include "SerialSend.h"



Cube::Cube (Serial* SPenter){
    this->SP = SPenter;
}
int Cube::Begin(){
    char output[1] = "";
    bool connectionCheck = 0;
    bool readyForUse = 0;
    while(!readyForUse){
        while(!connectionCheck){
            //Begin connection
            start:
            system("cls");
            printHeader();
            printf("Type the COM port number, if you don't know what is COM port or just don't know the port type N, if you want to exit type Q:");
            char firstMenu;
            if (scanf("%d", &firstMenu) < 1){
                scanf("%c", &firstMenu);
                if (firstMenu == 'q' || firstMenu == 'Q')
                    return 1;
                else if (firstMenu == 'n' || firstMenu == 'N'){
                    for (int i = 0;i <= 50; i++){
                        this->SP = new Serial(i, true);
                        if (this->SP->IsConnected()){
                            char connection;
                            printf("Connected at COM%d is this right?(Y/N)\n", i);
                            scanf(" %c", &connection);
                            if (connection == 'Y' || connection == 'y')
                                break; //terminates loop
                        }
                    if (i == 50){
                        system("cls");
                        printHeader();
                        printf("No COM ports available! Program is about to quit!\n");
                        Sleep(2000);
                        return 2;
                    }
                    }
                }
                else {
                    printf("Invalid entry\n");
                    Sleep(2000);
                    goto start;
                }
            }
            else this->SP = new Serial(firstMenu, false);
            connectionCheck = this->SP->IsConnected();
            Sleep(2000);
        }
        system("cls");
        printHeader();
        //Begin connection validation
        printf("We're connected! Now let's check the connection with the cube\n");
        char connectionTest[10] = {'c','o','n','n','e','c','t','i','o','n'};
        for (int i = 0; i < 10; i++){
            output[0] = connectionTest[i];
            this->SP->WriteData(output, 1);
        }
        char incomingData[256] = "";
        int readResult = 0;
        clock_t ti, tf;
        ti = clock();
        bool timeoutflag = false;
        do{
            Sleep(100);
            tf = clock();
            if (timediff(ti, tf) > 6200)
                timeoutflag = true;
            readResult = this->SP->ReadData(incomingData,255);
            printf(".");
        } while(readResult == 0 && !timeoutflag);
        incomingData[readResult] = 0;
        if (!strcmp(incomingData, "connection")){
             readyForUse = 1;
             printf("\nDone! The cube is ready!\n");
        }
        else {
            if (timeoutflag)
                 printf("\nConnection timed out! program will restart\n");
            else printf("\nConnection problems, please retry!\n");
            connectionCheck = 0;
        }
        Sleep(2000);
        system("cls");
        printHeader();
    }
    return 0;
}
void Cube::printHeader(){
    for (int i = 1; i <= 35; i++)
        printf(" ");
    printf("%c", 201);
    for (int i = 1; i <= 50; i++)
        printf("%c", 205);
    printf("%c \n", 187);
    for (int i = 1; i <= 35; i++)
        printf(" ");
    printf("%c", 186);
    printf("                 CubeShooter Game!                %c", 186);
    printf("\n");
    for (int i = 1; i <= 35; i++)
        printf(" ");
    printf("%c", 200);
    for (int i = 1; i <= 50; i++)
        printf("%c", 205);
    printf("%c \n", 188);
}
//Writes message to the Arduino and returns 1 if succes
bool Cube::Write(unsigned char* toWrite, int messageSize){
    char output[1];
    for (int i = 0; i < messageSize; i++){
        output[0] = toWrite[i];
        this->SP->WriteData(output, 1);
    }
    char incomingData[256] = "";
    int readResult = 0;
    clock_t ti, tf;
    ti = clock();
    bool timeoutflag = false;
    do{
        tf = clock();
        if (timediff(ti, tf) > 20)
            return 0;
        readResult = this->SP->ReadData(incomingData,255);
    } while(readResult == 0 && !timeoutflag);
    return incomingData[0];
}
//Sets a bit in the array to print in the cube (returns 0 if not able to set)
bool Cube::setPosition(int x, int y, int z, bool isOn){
    if ((0 < x < 6) && (0 < y < 6) && (0 < z < 6))
        cubeToPrint[x-1][y-1][z-1] = isOn;
    else return 0;
    return 1;
}
//Gets the state of a cube led
bool Cube::getPosition(int x, int y, int z){
    return cubeToPrint[x-1][y-1][z-1];
}
//Writes the next cube into the real cube
bool Cube::Print(){
    for (int i = 0, positionToSend = 0, rawDataSelect = 0, aux = 0; i <= 128; i++, positionToSend++){
        if (positionToSend < 8){
            aux <<= 1;
            aux += cubeToPrint[i%5][(i/5)%5][i/25];
        }
        else {
            for (int j = 0; j < 8; j++){
                rawData[rawDataSelect] <<= 1;
                rawData[rawDataSelect] += aux%2;
                aux >>= 1;
            }
            positionToSend = -1;
            rawDataSelect++;
            i--;
        }
    }
    this->Write(rawData, 16);
}
//Starts the game by printing the initial message
void Cube::Start(){
    unsigned int volume;
    volume = 0xFFFFFFFF;
    PlaySound("C:\\CubeShooterGame\\MainSound.WAV", NULL, SND_ASYNC);
    waveOutSetVolume(NULL, volume);
    Sleep(500);
    GetAsyncKeyState(VK_RETURN);
    int flag = 0;
    clock_t ti, tf;
    ti = clock();
    char Welcome[779] ="Not so far in time...in a nearby galaxy...     \n\n";
       strcat(Welcome, "Two ships traveled by their own                \n\n");
       strcat(Welcome, "They got trapped by a mysterious force         \n\n");
       strcat(Welcome, "In some kind of Cube...                        \n\n");
       strcat(Welcome, "Suddenly the space around became pixels        \n\n");
       strcat(Welcome, "They stayed there for a long time...           \n\n");
       strcat(Welcome, "But finally they figured out a way...          \n\n");
       strcat(Welcome, "To break free!                                 \n\n");
       strcat(Welcome, "If they run very fast they could open a breach \n\n");
       strcat(Welcome, "In space time!                                 \n\n");
       strcat(Welcome, "Therefore, they could create a portal          \n\n");
       strcat(Welcome, "Leading home!                                  \n\n");
       strcat(Welcome, "But that would need a tremendous amount of fuel\n\n");
       strcat(Welcome, "Someone would be left behind...                \n\n");
       strcat(Welcome, "But none of them wanted to stay there forever  \n\n");
       strcat(Welcome, "So...They decided to FIGHT!                    \n\n");
    for(int i = 0; i < 779; i++){
        printf("%c", Welcome[i]);
        Sleep(100);
        Clear();
        setPosition( (i/5)%5 + 1, i%5 + 1, (i/25)%5+1, 1);
        Print();
        if (i == 763)
            flag = 1;
        if (GetAsyncKeyState(VK_RETURN))
            flag = 1;
        if (flag)
            volume-= 0x11111111;
        if (!volume){
            PlaySound(NULL, 0, 0);
            return;
        }
        waveOutSetVolume(NULL, volume);
    }
    Sleep(500);
}
//Ends the game by printing the final message
void Cube::End(int Winner){
    unsigned int volume;
    volume = 0xFFFFFFFF;
    PlaySound("C:\\CubeShooterGame\\FinalSound.WAV", NULL, SND_ASYNC);
    waveOutSetVolume(NULL, volume);
    Sleep(500);
    GetAsyncKeyState(VK_RETURN);
    int flag = 0;
    clock_t ti, tf;
    ti = clock();
    char Welcome[779]="\nYou have done it!                             \n\n";
       strcat(Welcome, "After destroying your opponent you successfully\n\n");
       strcat(Welcome, "Achieved enough power to break free...         \n\n");
       strcat(Welcome, "Now you can run away!                          \n\n");
       strcat(Welcome, "                                               \n\n");
       strcat(Welcome, "New adventures wait for you!                   \n\n");
       strcat(Welcome, "Now enjoy your rest!                           \n\n");
       strcat(Welcome, "                                               \n\n");
       strcat(Welcome, "This game was produced by Aloysio Galvao Lopes \n\n");
       strcat(Welcome, "All the sounds were obtained in YouTube        \n\n");
       strcat(Welcome, "And all the learning to make this possible     \n\n");
       strcat(Welcome, "Is credited to Google = )                      \n\n");
       strcat(Welcome, "I hope you enjoyed the game!                   \n\n");
       strcat(Welcome, "Thank you for playing!                         \n\n");
       strcat(Welcome, "Always remember...      Cards!                 \n\n");
       strcat(Welcome, "Press enter to return to main menu...          \n\n");
    for(int i = 0; i < 779; i++){
        printf("%c", Welcome[i]);
        Sleep(100);
        if (Winner == 1 && !(i%5)){
            setPosition(2, 5, 4, 1);
            setPosition(3, 5, 5, 1);
            setPosition(3, 5, 4, 1);
            setPosition(3, 5, 3, 1);
            setPosition(3, 5, 2, 1);
            setPosition(4, 5, 1, 1);
            setPosition(3, 5, 1, 1);
            setPosition(2, 5, 1, 1);
        }
        else if (Winner == 2 && !(i%5)){
            setPosition(4, 5, 2, 1);
            setPosition(2, 5, 4, 1);
            setPosition(3, 5, 5, 1);
            setPosition(4, 5, 5, 1);
            setPosition(5, 5, 4, 1);
            setPosition(5, 5, 3, 1);
            setPosition(3, 5, 2, 1);
            setPosition(5, 5, 1, 1);
            setPosition(4, 5, 1, 1);
            setPosition(3, 5, 1, 1);
            setPosition(2, 5, 1, 1);
        }
        Print();
        for(int i = 1; i <= 5; i++)
            for(int k = 1; k <= 5; k++)
                for(int j = 1; j <= 4; j++){
                    setPosition(i,j,k, getPosition(i,j+1,k));
        }
    for(int i = 1; i <= 5; i++)
        for(int k = 1; k <= 5; k++)
            setPosition(i, 5, k, 0);
        if (GetAsyncKeyState(VK_RETURN))
            flag = 1;
        if (flag)
            volume-= 0x11111111;
        if (!volume){
            PlaySound(NULL, 0, 0);
            return;
        }
        waveOutSetVolume(NULL, volume);
    }
    while(1){
        if (GetAsyncKeyState(VK_RETURN)){
            do{
                volume-= 0x11111111;
                waveOutSetVolume(NULL, volume);
                Sleep(100);
            }while(volume);
            PlaySound(NULL, 0, 0);
            return;
        }
    }
}
//Prints GET READY!
void Cube::GetReady(){
    char GetReady[11] = "GET READY!";
    printf("                                                         ");
    for(int i = 0; i < 11; i++){
        printf("%c", GetReady[i]);
        Sleep(100);
    }
}
//Prints the GAME OVER MESSAGE
void Cube::GameOver(int winner){
    Clear();
    system("cls");
    printHeader();
    PlaySound("C:\\CubeShooterGame\\GameOverSound.WAV", NULL, SND_ASYNC);
    char GameOver[10] = "GAME OVER";
    printf("                                                         ");
    for(int i = 0; i < 10; i++){
        printf("%c", GameOver[i]);
        Sleep(100);
    }
    printf("\n");
    char Winner[24] = "CONGRATULATIONS PLAYER ";
    printf("                                                   ");
    for(int i = 0; i < 24; i++){
        printf("%c", Winner[i]);
        Sleep(100);
    }
    printf("%d", winner);
    Sleep(500);
}
//Prints the menu and gives the player the options
int Cube::Menu(){
    waveOutSetVolume(NULL, 0xFFFFFFFF);
    Clear();
    Print();
    PlaySound("C:\\CubeShooterGame\\MenuSound.WAV", NULL, SND_LOOP | SND_ASYNC);
    system("cls");
    printHeader();
    GetAsyncKeyState(VK_RETURN);
    printf("Welcome to CubeShooter Game! Your mission is to destroy the other player and break free!\n");
    printf("Use the arrows to move and enter to shoot in player 1 and WASD and H for player 2\n");
    printf("Press ENTER to begin or ESC to quit...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t\tby Aloysio Galvao Lopes");
    while(1){
        menuAnim();
        if (GetAsyncKeyState(VK_RETURN)){
            system("cls");
            posPlayer1 = 12;
            posPlayer2 = 12;
            printHeader();
            Clear();
            Print();
            unsigned int volume;
            volume = 0xFFFFFFFF;
            do{
                volume-= 0x11111111;
                waveOutSetVolume(NULL, volume);
                Sleep(100);
            }while(volume);
            PlaySound(NULL, 0, 0);
            GetReady();
            initAnim();
            return 0;
        }
        if (GetAsyncKeyState(VK_ESCAPE))
            return 1;
    }
}
//Prints menu animation
void Cube::menuAnim(){
    setPosition(rand()%5 + 1, 5, rand()%5 + 1, 1);
    Print();
    Sleep(100);
    for(int i = 1; i <= 5; i++)
        for(int k = 1; k <= 5; k++)
            for(int j = 1; j <= 4; j++){
                setPosition(i,j,k, getPosition(i,j+1,k));
            }
    for(int i = 1; i <= 5; i++)
        for(int k = 1; k <= 5; k++)
            setPosition(i, 5, k, 0);
}
//Prints the initial animation
void Cube::initAnim(){
        waveOutSetVolume(NULL, 0xFFFFFFFF);
        PlaySound("C:\\CubeShooterGame\\GameSound.WAV", NULL, SND_LOOP | SND_ASYNC);
        setPosition(3,3,3,1);
        Print();
        Sleep(100);
        Clear();
        setPosition(2,3,3,1);
        setPosition(4,3,3,1);
        setPosition(3,2,3,1);
        setPosition(3,4,3,1);
        setPosition(3,3,2,1);
        setPosition(3,3,4,1);
        Print();
        Sleep(100);
        Clear();
        setPosition(2,3,3,1);
        setPosition(4,3,3,1);
        setPosition(3,2,3,1);
        setPosition(3,4,3,1);
        setPosition(3,3,2,1);
        setPosition(3,3,4,1);
        setPosition(2,2,4,1);
        setPosition(2,2,2,1);
        setPosition(4,2,2,1);
        setPosition(4,2,4,1);
        setPosition(2,4,2,1);
        setPosition(2,4,4,1);
        setPosition(4,4,4,1);
        setPosition(4,4,2,1);
        Print();
        Sleep(100);
        Clear();
        setPosition(1,3,3,1);
        setPosition(5,3,3,1);
        setPosition(3,1,3,1);
        setPosition(3,5,3,1);
        setPosition(3,3,1,1);
        setPosition(3,3,5,1);
        setPosition(2,2,4,1);
        setPosition(2,2,2,1);
        setPosition(4,2,2,1);
        setPosition(4,2,4,1);
        setPosition(2,4,2,1);
        setPosition(2,4,4,1);
        setPosition(4,4,4,1);
        setPosition(4,4,2,1);
        Print();
        Sleep(100);
        Clear();
        setPosition(2,5,2,1);
        setPosition(2,5,4,1);
        setPosition(3,5,3,1);
        setPosition(4,5,4,1);
        setPosition(4,5,2,1);
        setPosition(2,1,2,1);
        setPosition(2,1,4,1);
        setPosition(3,1,3,1);
        setPosition(4,1,4,1);
        setPosition(4,1,2,1);
        setPosition(4,5,2,1);
        setPosition(5,4,2,1);
        setPosition(5,2,2,1);
        setPosition(5,4,4,1);
        setPosition(5,2,4,1);
        setPosition(5,3,3,1);
        setPosition(1,4,2,1);
        setPosition(1,2,2,1);
        setPosition(1,4,4,1);
        setPosition(1,2,4,1);
        setPosition(1,3,3,1);
        setPosition(2,4,1,1);
        setPosition(4,2,1,1);
        setPosition(4,4,1,1);
        setPosition(2,2,1,1);
        setPosition(3,3,1,1);
        setPosition(2,4,5,1);
        setPosition(4,2,5,1);
        setPosition(4,4,5,1);
        setPosition(2,2,5,1);
        setPosition(3,3,5,1);
        Print();
        Sleep(100);
        Clear();
}
//Shows the animation of the player being destroyed
void Cube::PlayerShot(int x, int y, int z){
    Sleep(75);
    setPosition(x, y, z, 0);
    if (y-1 > 0)
        setPosition(x, y-1, z,1);
    if (y+1 < 6)
        setPosition(x, y+1, z,1);
    if (z-1 > 0)
        setPosition(x, y, z-1,1);
    if (z+1 < 6)
        setPosition(x, y, z+1,1);
    Print();
    Sleep(75);
    if (y-1 > 0)
        setPosition(x, y-1, z,0);
    if (y+1 < 6)
        setPosition(x, y+1, z,0);
    if (z-1 > 0)
        setPosition(x, y, z-1,0);
    if (z+1 < 6)
        setPosition(x, y, z+1,0);
    if (y-2 > 0)
        setPosition(x, y-2, z,1);
    if (y+2 < 6)
        setPosition(x, y+2, z,1);
    if (z-2 > 0)
        setPosition(x, y, z-2,1);
    if (z+2 < 6)
        setPosition(x, y, z+2,1);
    Print();
    Sleep(75);
    if (y-2 > 0)
        setPosition(x, y-2, z,0);
    if (y+2 < 6)
        setPosition(x, y+2, z,0);
    if (z-2 > 0)
        setPosition(x, y, z-2,0);
    if (z+2 < 6)
        setPosition(x, y, z+2,0);

}
//Prints the life
void Cube::PrintLife(){
    printf("Player 1 Life:");
    for (int i = 1; i <= Life1; i++)
        printf(" ||");
    printf("\n");
    printf("Player 2 Life:");
    for (int i = 1; i <= Life2; i++)
        printf(" ||");
    printf("\n");
    if (Ammo1 < MAXAMMO){
    printf("Player 1 Reloading:");
        for (int i = Ammo1; i <= MAXAMMO; i++)
            printf(" .");
        printf("\n");
    }
    if (Ammo2 < MAXAMMO){
    printf("Player 2 Reloading:");
        for (int i = Ammo2; i <= MAXAMMO; i++)
            printf(" .");
        printf("\n");
    }
}
//Prints the score
int Cube::PrintScore(){
        this->Life1 = LIFE;
        this->Life2 = LIFE;
        this->Ammo1 = MAXAMMO;
        this->Ammo2 = MAXAMMO;
        this->AmmoChange = 0;
        system("cls");
        printHeader();
        PrintLife();
}
//Makes the player go up
void Cube::PlayerGoUp(int play){
    if (!play)
            this->posPlayer1 = (this->posPlayer1 + 5)%25;
    else    this->posPlayer2 = (this->posPlayer2 + 5)%25;

}
//Makes the player go down
void Cube::PlayerGoDown(int play){
    if (!play){
            this->posPlayer1 = this->posPlayer1 - 5;
            if(this->posPlayer1 < 0)
                this->posPlayer1 += 25;
    }
    else{
            this->posPlayer2 = this->posPlayer2 - 5;
            if(this->posPlayer2 < 0)
                this->posPlayer2 += 25;
    }
}
//Makes the player go left
void Cube::PlayerGoLeft(int play){
    if (!play)
            this->posPlayer1 = (this->posPlayer1 + 1)%5 + (this->posPlayer1/5)*5;
    else    this->posPlayer2 = (this->posPlayer2 + 1)%5 + (this->posPlayer2/5)*5;

}
//Makes the player go Right
void Cube::PlayerGoRight(int play){
    if (!play){
            if(this->posPlayer1%5 - 1 < 0)
                 this->posPlayer1 = this->posPlayer1 + 4;
            else this->posPlayer1 = (this->posPlayer1 - 1)%5 + (this->posPlayer1/5)*5;
    }
    else{
            if(this->posPlayer2%5 - 1 < 0)
                 this->posPlayer2 = this->posPlayer2 + 4;
            else this->posPlayer2 = (this->posPlayer2 - 1)%5 + (this->posPlayer2/5)*5;
    }
}
//Makes the player go shoot
void Cube::PlayerShoot(int play){
    if (!play && (Ammo1 == MAXAMMO)){
            shootMatrix1[4][this->posPlayer1%5][this->posPlayer1/5] = 1;
            Ammo1 = 0;
            AmmoChange = 1;
    }
    else if (play && (Ammo2 == MAXAMMO)){
            shootMatrix2[0][this->posPlayer2%5][this->posPlayer2/5] = 1;
            Ammo2 = 0;
            AmmoChange = 1;
    }
//    PlaySound("C:\\CubeShooterGame\\ShipDestroy.WAV", NULL, SND_ASYNC);
}
//Writes the player to the face s
void Cube::WritePlayers(){
    for (int i = 1; i <= 5; i++){
        for (int j = 1; j <= 5; j++){
            setPosition(5, i, j, 0);
            setPosition(1, i, j, 0);
        }
    }
    setPosition(5, posPlayer1%5 + 1, posPlayer1/5 + 1, 1);
    setPosition(1, posPlayer2%5 + 1, posPlayer2/5 + 1, 1);
}
//Prints the shoots
void Cube::PrintMatrixShoot(){
     for (int i = 1; i <= 5; i++)
        for(int j = 1; j <= 5; j++)
            for(int k = 1; k <= 5; k++)
                if (shootMatrix1[i-1][j-1][k-1] || shootMatrix2[i-1][j-1][k-1])
                     setPosition(i, j, k, 1);
    Sleep(5);
    Print();
    for (int i = 2; i <= 4; i++)
        for(int j = 1; j <= 5; j++)
            for(int k = 1; k <= 5; k++)
                setPosition(i, j, k, 0);
    Sleep(5);
    Print();
    for (int i = 0; i < 4; i++)
        for(int k = 0; k < 5; k++)
            for(int j = 0; j < 5; j++){
                shootMatrix1[i][j][k] = shootMatrix1[i+1][j][k];
                shootMatrix2[4-i][j][k] = shootMatrix2[3-i][j][k];
            }
    for(int k = 0; k < 5; k++)
            for(int j = 0; j < 5; j++){
                shootMatrix1[4][j][k] = 0;
                shootMatrix2[0][j][k] = 0;
            }
}
//Controls the scoreboard
int Cube::GameControl(){
    if (shootMatrix1[0][posPlayer2%5][posPlayer2/5]){
        for (int i = 0; i < 5; i++)
            for(int k = 0; k < 5; k++)
                for(int j = 0; j < 5; j++){
                    shootMatrix1[i][j][k] = 0;
                    shootMatrix2[i][j][k] = 0;
                }
        Life2--;
        if (!Life2){
            GameOver(1);
            End(1);
            return 0;
        }
        PlaySound("C:\\CubeShooterGame\\ShipDestroy.WAV", NULL, SND_ASYNC);
        system("cls");
        printHeader();
        PrintLife();
        PlayerShot(1, posPlayer2%5 + 1, posPlayer2/5 +1);
        initAnim();
        Ammo1 = MAXAMMO;
        Ammo2 = MAXAMMO;
        posPlayer1 = 18;
        posPlayer2 = 6;
        WritePlayers();
        Print();
        GetReady();
    }
    if (shootMatrix2[4][posPlayer1%5][posPlayer1/5]){
        for (int i = 0; i < 5; i++)
            for(int k = 0; k < 5; k++)
                for(int j = 0; j < 5; j++){
                    shootMatrix1[i][j][k] = 0;
                    shootMatrix2[i][j][k] = 0;
                }
        Life1--;
        if (!Life1){
            GameOver(2);
            End(2);
            return 0;
        }
        PlaySound("C:\\CubeShooterGame\\ShipDestroy.WAV", NULL, SND_ASYNC);
        system("cls");
        printHeader();
        PrintLife();
        PlayerShot(5, posPlayer1%5 + 1, posPlayer1/5 +1);
        initAnim();
        Ammo1 = MAXAMMO;
        Ammo2 = MAXAMMO;
        posPlayer1 = 6;
        posPlayer2 = 18;
        WritePlayers();
        Print();
        GetReady();
    }
    if (AmmoChange){
        if (Ammo1 < 10)
            Ammo1++;
        if (Ammo2 < 10)
            Ammo2++;
        system("cls");
        printHeader();
        PrintLife();
    }
    if (Ammo1 == MAXAMMO && Ammo2 == MAXAMMO)
        AmmoChange = false;
    return 1;
}
//Clear the cube
void Cube::Clear(){
    for (int i = 1; i <= 5; i++)
        for(int j = 1; j <= 5; j++)
            for(int k = 1; k <= 5; k++)
                setPosition(i , j, k, 0);
}
//Function for time difference
long Cube::timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}
