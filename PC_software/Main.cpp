#include"SerialSend.h"

int main(){
    //Creating the objects
    Serial* SP;
    Cube cube(SP);
    //Needed variables
    int leave;
    clock_t ti, tf;
    //Returning error messages
    int conectErr = cube.Begin();
    if (conectErr)
        return conectErr;
    //Beginning game
    cube.Start();
    do{
        int game = 1;
        leave = cube.Menu();
        if (!leave)
            cube.PrintScore();
        else game = 0;
            tf = clock();
        while(game){
            cube.Print();
            ti = clock();
            if (cube.timediff(tf, ti) > 40){
            tf = clock();
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
            game = cube.GameControl();
            cube.PrintMatrixShoot();
            cube.WritePlayers();
             if (GetAsyncKeyState(VK_ESCAPE)){
                    game = 0;
                }
            Sleep(5);
        }
    }while(!leave);
    return 0;
}

//Returns: 0 -> program went normal
//         1 -> user aborted
//         2 -> connection error
