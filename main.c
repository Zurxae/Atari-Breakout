#include "include/raylib.h"

#define WIDTH 60
#define HEIGHT 40
#define PADDING 10
#define GRID_ROW 13
#define PLAYER_WIDTH 150
#define PLAYER_HEIGHT 10
#define BALL_RADIUS 12

//Returns the absolute value of the values in a Vector2 struct
void AbsX(Vector2 *vPtr);

int main(void)
{
    //Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Game: Atari Breakout");

    //Set frames-per-second of game
    SetTargetFPS(60);

    //Block Construct
    typedef struct _block
    {
        int x;
        int y;
        int status;
    } Block;

    Block blockArray[GRID_ROW] = {0};

    for (int i = 0; i < GRID_ROW; i++)
    {
        blockArray[i] = (Block){i, 0, 1};
    }

    //Player Construct
    Vector2 playerPos;
    playerPos.x = (screenWidth / 2) - (PLAYER_WIDTH / 2);
    playerPos.y = (screenHeight - 25);

    //Ball Construct
    Vector2 ballPos = {(screenWidth / 2), (screenHeight - 25 - BALL_RADIUS)};
    Vector2 ballSpeed = {5.0f, 4.0f};

    bool playing_status = 0;
    //bool collision = 0;

    //Main game loop
    while (!WindowShouldClose())
    {

        //Update

        //Player Position
        if (IsKeyDown(KEY_LEFT))
        {
            playerPos.x -= 6.0f;
            //playing_status = 1;
        }
        if (IsKeyDown(KEY_RIGHT))
        {
            playerPos.x += 6.0f;
            //playing_status = 1;
        }

        //Ball Physics

        if (!playing_status)
        {
            ballPos.x += ballSpeed.x;
            ballPos.y += ballSpeed.y;
        }

        //Collision

        //Collision with walls
        if ((ballPos.x >= (screenWidth - BALL_RADIUS)) || (ballPos.x <= BALL_RADIUS))
        {
            ballSpeed.x *= -1.0f;
        }
        if ((ballPos.y >= (screenHeight - BALL_RADIUS)) || (ballPos.y <= BALL_RADIUS))
        {
            ballSpeed.y *= -1.0f;
        };

        //Collision with player (Splitting the bar into three parts: left, middle, right)
        /*
        if ((ballPos.x >= playerPos.x) && (ballPos.x <= (playerPos.x + PLAYER_WIDTH)) && (ballPos.y >= playerPos.y) && (ballPos.y <= (playerPos.y + PLAYER_HEIGHT)))
        {
            ballSpeed.x *= -1.0f;
            ballSpeed.y *= -1.0f;
        }
        */
        //Left
        if ((ballPos.x >= (playerPos.x - BALL_RADIUS)) && (ballPos.x < (playerPos.x - BALL_RADIUS + (0.33f * PLAYER_WIDTH))) && (ballPos.y >= (playerPos.y - BALL_RADIUS)) && (ballPos.y <= (playerPos.y + PLAYER_HEIGHT - BALL_RADIUS)))
        {
            AbsX(&ballSpeed);
            ballSpeed.x *= -1.0f;
            ballSpeed.y *= -1.0f;
        }

        //Middle
        if ((ballPos.x >= (playerPos.x - BALL_RADIUS + (0.33f * PLAYER_WIDTH))) && (ballPos.x < (playerPos.x - BALL_RADIUS + (0.66f * PLAYER_WIDTH))) && (ballPos.y >= (playerPos.y - BALL_RADIUS)) && (ballPos.y <= (playerPos.y + PLAYER_HEIGHT - BALL_RADIUS)))
        {
            ballSpeed.y *= -1.0f;
        }

        //Right
        if ((ballPos.x >= (playerPos.x - BALL_RADIUS + (0.66f * PLAYER_WIDTH))) && (ballPos.x <= (playerPos.x - BALL_RADIUS + PLAYER_WIDTH)) && (ballPos.y >= (playerPos.y - BALL_RADIUS)) && (ballPos.y <= (playerPos.y + PLAYER_HEIGHT - BALL_RADIUS)))
        {
            AbsX(&ballSpeed);
            ballSpeed.y *= -1.0f;
        }

        //Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //Player
        DrawRectangle(playerPos.x, playerPos.y, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);

        //Ball
        DrawCircleV(ballPos, BALL_RADIUS, RED);

        //Grid
        for (int i = 0; i < GRID_ROW; i++)
        {
            if (blockArray[i].status == 1)
            {
                int x = blockArray[i].x * WIDTH;
                DrawRectangle(x, blockArray[i].y, WIDTH - PADDING, HEIGHT - PADDING, GRAY);

                if (((ballPos.x >= x) && (ballPos.x <= x + WIDTH - PADDING) && (ballPos.y >= blockArray[i].y) && (ballPos.y <= blockArray[i].y + HEIGHT - PADDING)))
                {
                    blockArray[i].status = 0;
                    ballSpeed.x *= -1.0f;
                    ballSpeed.y *= -1.0f;
                }
            }
        }
        EndDrawing();
    }

    //De-Initialization
    CloseWindow();

    return 0;
}

//Function Definitions
void AbsX(Vector2 *vPtr)
{
    if ((vPtr->x) >= 0)
    {
        vPtr->x *= 1.0f;
    }
    else
    {
        vPtr->x *= -1.0f;
    }
}