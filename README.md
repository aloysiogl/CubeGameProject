# Shooter game in a LED Cube

This project is a shooter game which runs in a 5x5x5 LED Cube. The project was made using code::blocks, Arduino and Windows serial communications.

The cube is controlled using four shift registers and an Aduino. The Arduino handles a basic array representation of the cube and uses serial communication to connect to the PC. There have been implemented several animation in the Arduino code, so the Arduino and the cube on their own are able to present some interesting animations.

When serial communication to the PC is established the user is able to play a simple game using the cube. In the game two players are placed on in each face of the cube and the objective is to shoot and therefore kill the opponent. The game's interface is pretty simple: it is, initially, presented a story, and then it is possible to start the game in the menu. All the interface is made via command line.

The PC code handles communication in different levels of abstraction and stores the cube state in a more abstract three dimensional matrix. Using the abstractions provided by the Cube class in the SerialSend code it is possible to control the whole cube in the game interface.
