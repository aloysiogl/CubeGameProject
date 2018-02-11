#include"SerialSend.h"

int main(){
    //Creating serial connection objects
    Serial* SP;
    Cube cube(SP);

    //Needed time and leave variables
    int leave;
    clock_t ti, tf;

    //Returning error messages in connection process
    int conectErr = cube.Begin();
    if (conectErr)
        return conectErr;

    //Beginning game
    cube.Start();

    //Go back to the menu loop
    do{
        int game = 1;
        leave = cube.Menu();
        if (!leave)
            cube.PrintScore();
        else game = 0;
            tf = clock();

        //Game loop
        while(game){
            cube.Print();
            ti = clock();
            if (cube.timediff(tf, ti) > 40){
            tf = clock();

                //Getting keystrikes
                if (GetAsyncKeyState(VK_UP)){
                    cube.PlayerGoUp(0);
                }
                if (GetAsyncKeyState(VK_DOWN)){
                    cube.PlayerGoDown(0);
                }
                if (GetAsyncKeyState(VK_LEFT)){
                    cube.PlayerGoLeft(0);
                }
                if (GetAsyncKeyState(VK_RIGHT)){
                    cube.PlayerGoRight(0);
                }
                if (GetAsyncKeyState(VK_RETURN)){
                    cube.PlayerShoot(0);
                }
                if (GetAsyncKeyState(0x57)){
                    cube.PlayerGoUp(1);
                }
                if (GetAsyncKeyState(0x53)){
                    cube.PlayerGoDown(1);
                }
                if (GetAsyncKeyState(0x41)){
                    cube.PlayerGoLeft(1);
                }
                if (GetAsyncKeyState(0x44)){
                    cube.PlayerGoRight(1);
                }
                if (GetAsyncKeyState(0x48)){
                    cube.PlayerShoot(1);
                }
            }

            //Chacking if the game is over
            game = cube.GameControl();

            //Printing the game state
            cube.PrintMatrixShoot();
            cube.WritePlayers();

            //If escape is pressed the game is over
            if (GetAsyncKeyState(VK_ESCAPE)){
                    game = 0;
                }
            Sleep(5);
        }
    }while(!leave);
    return 0;
}

//Program returns: 0 -> program went normal
//                 1 -> user aborted
//                 2 -> connection error
