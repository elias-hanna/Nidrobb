#ifndef GAMEPARAM_HPP
#define GAMEPARAM_HPP

//Toujours tout recompiler à la modification des paramètres

//Paramètre Affichage
#define MIN_LOOP_TIME 17 //60 FPS
//#define MIN_LOOP_TIME 33 //30 FPS

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_BPP 32

//Paramètre environement
#define WALL_THICKNESS 40

#define P1_START_POSX 50
#define P1_START_POSY 250
#define P2_START_POSX SCREEN_WIDTH-100
#define P2_START_POSY 250

//Paramètre joueur
#define PLAYER_HEIGHT 100
#define PLAYER_WIDTH 50
#define PLAYER_JUMP_HEIGHT 150
#define PLAYER_MOVE_DISTANCE 40
#define PLAYER_FALL_SPEED 20
#define PLAYER_KNOCKBACK 50

#endif