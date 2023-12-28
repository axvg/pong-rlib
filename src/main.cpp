#include <iostream>
#include <raylib.h>
#include "Ball.h"
#include "Paddle.h"

Sound hitSound;
Sound scoreSound;

int main(){
    InitWindow(800, 600, "Pong!");
    SetWindowState(FLAG_VSYNC_HINT);

    InitAudioDevice();
    hitSound = LoadSound("assets/hit.mp3");
    scoreSound = LoadSound("assets/score.mp3");
    
    Ball ball;
    ball.x = GetScreenWidth()/2;
    ball.y = GetScreenHeight()/2;
    ball.radius = 5;
    ball.speedX = 300;
    ball.speedY = 300;

    Paddle player1;
    player1.x = 50;
    player1.y = GetScreenHeight()/2 - 50;
    player1.width = 10;
    player1.height = 100;
    player1.speedY = 300;

    Paddle player2;
    player2.x = GetScreenWidth() - 50;
    player2.y = GetScreenHeight()/2 - 50;
    player2.width = 10;
    player2.height = 100;
    player2.speedY = 300;

    const char* winnerStr = nullptr;

    while (!WindowShouldClose()){
        ball.x += 1 * GetFrameTime() * ball.speedX;
        ball.y += 1 * GetFrameTime() * ball.speedY;

        if (ball.y > GetScreenHeight() - ball.radius || ball.y < ball.radius){
            ball.speedY *= -1;
        }

        // if (ball.x > GetScreenWidth() - ball.radius || ball.x < ball.radius){
        //     ball.speedX *= -1;
        // }

        if (IsKeyDown(KEY_W) && player1.y > 0){
            player1.y -= 1 * GetFrameTime() * player1.speedY;
        }
        if (IsKeyDown(KEY_S) && player1.y < GetScreenHeight() - player1.height){
            player1.y += 1 * GetFrameTime() * player1.speedY;
        }

        if (IsKeyDown(KEY_UP) && player2.y > 0){
            player2.y -= 1 * GetFrameTime() * player2.speedY;
        }
        if (IsKeyDown(KEY_DOWN) && player2.y < GetScreenHeight() - player2.height){
            player2.y += 1 * GetFrameTime() * player2.speedY;
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player1.x, player1.y, player1.width, player1.height})){
            if (ball.speedX < 0){
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - player1.y) / (player1.height/2) * ball.speedX;
                PlaySound(hitSound);
            }
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player2.x, player2.y, player2.width, player2.height})){
            if (ball.speedX > 0){
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - player2.y) / (player2.height/2) * ball.speedX * -1;
                PlaySound(hitSound);
            }
        }

        if (ball.x < 0){
            winnerStr = "Player 2 wins!";
        } else if (ball.x > GetScreenWidth()){
            winnerStr = "Player 1 wins!";
        }

        if (winnerStr != nullptr){
            if (IsKeyPressed(KEY_SPACE)){
                ball.x = GetScreenWidth()/2;
                ball.y = GetScreenHeight()/2;
                ball.speedX = 300;
                ball.speedY = 300;
                player1.y = GetScreenHeight()/2 - 50;
                player2.y = GetScreenHeight()/2 - 50;
                player1.x = 50;
                player2.x = GetScreenWidth() - 50;
                winnerStr = nullptr;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        ball.Draw();
        player1.Draw();
        player2.Draw();

        if (winnerStr != nullptr){
            // undraw ball and paddles
            ball.x = -100;
            player1.x = -100;
            player2.x = -100;
            DrawText(winnerStr, GetScreenWidth()/2 - MeasureText(winnerStr, 40)/2, GetScreenHeight()/2 - 40, 40, WHITE);
            PlaySound(scoreSound);
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();

    UnloadSound(hitSound);
    UnloadSound(scoreSound);
    CloseAudioDevice();

    return 0;
}
