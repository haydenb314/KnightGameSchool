#include <iostream>
#include "raylib.h"

void playAnimation() {

}

int main() {

    InitWindow(1600, 900, "Knight Game");
    SetTargetFPS(60);

    Texture2D knightSheet = LoadTexture("knight_sheet.png");

    //dimensions of a singular frame
    const float frameWidth = static_cast<float>(knightSheet.width) / 12;
    float frameHeight = static_cast<float>(knightSheet.height) / 30;

    //flips knight animation when moving backwards
    float currentFrameWidth = frameWidth;
    float flippedFrameWidth = -frameWidth;

    //timer
    float timer = 0.f;
    float timePerFrame = .12;

    //frames
    int frame = 0;

    //structure to hold animation max frames + rectangle
    struct AnimationStruct {
        float animationHeight;
        int maxFrames;
    };

    //animation structs
    AnimationStruct attackAnimation;
    attackAnimation.animationHeight = 0;
    attackAnimation.maxFrames = 4;

    AnimationStruct attack2Animation;
    attack2Animation.animationHeight = knightSheet.height - (frameHeight * 28);
    attack2Animation.maxFrames = 6;

    AnimationStruct idleAnimation;
    idleAnimation.animationHeight = knightSheet.height - (frameHeight * 14);
    idleAnimation.maxFrames = 10;

    AnimationStruct jumpAnimation;
    jumpAnimation.animationHeight = knightSheet.height - (frameHeight * 13);
    jumpAnimation.maxFrames = 3;

    AnimationStruct crouchAnimation;
    crouchAnimation.animationHeight = knightSheet.height - (frameHeight * 20);
    crouchAnimation.maxFrames = 1;

    AnimationStruct crouch_walkAnimation;
    crouch_walkAnimation.animationHeight = knightSheet.height - (frameHeight * 20);
    crouch_walkAnimation.maxFrames = 8;

    AnimationStruct runAnimation;
    runAnimation.animationHeight = knightSheet.height - (frameHeight * 10);
    runAnimation.maxFrames = 10;

    //holds current animation
    AnimationStruct currentAnimation;
    currentAnimation.maxFrames = 10;

    //position
    float currentX = 0;
    float currentY = 300;

    //jump physics
    float gravity = 500;
    float velocityY = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(PURPLE);

        timer += GetFrameTime();

        if (timer >= timePerFrame) {
            timer = 0.0f;
            frame += 1;
        }

        frame = frame % currentAnimation.maxFrames;

        velocityY += GetFrameTime() * gravity;
        currentY += GetFrameTime() * velocityY;

        if (IsKeyPressed(KEY_W)) {
            velocityY = -300;
            timePerFrame = .12;
            currentAnimation = jumpAnimation;
        } else if (IsKeyDown(KEY_D)) {
            currentFrameWidth = frameWidth;
            currentAnimation = runAnimation;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                currentX += 10;
                timePerFrame = .08;
            } else if (IsKeyDown(KEY_S)) {
                currentX += 4;
                timePerFrame = .14;
                currentAnimation = crouch_walkAnimation;
            } else {
                currentX += 5;
                timePerFrame = .12;
            }
        } else if (IsKeyDown(KEY_A)) {
            currentFrameWidth = flippedFrameWidth;
            currentAnimation = runAnimation;
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                currentX -= 10;
                timePerFrame = .08;
            } else if (IsKeyDown(KEY_S)) {
                currentX -= 4;
                timePerFrame = .14;
                currentAnimation = crouch_walkAnimation;
            } else {
                currentX -= 5;
                timePerFrame = .12;
            }
        } else if (IsKeyDown(KEY_S)) {
            currentAnimation = crouchAnimation;
        } else if (IsKeyDown(KEY_G)) {
            currentAnimation = attack2Animation;
            timePerFrame = .12;
        } else if (IsKeyDown(KEY_H)) {
            currentAnimation = attackAnimation;
            timePerFrame = .12;
        } else {
            currentAnimation = idleAnimation;
            timePerFrame = .12;
        }

        //makes sure knight doesn't fall through floor
        if (currentY >= 300) {
            currentY = 300;
        }

        //keeps knight on screen by sending it to opposite side if offscreen
        if (currentX >= 1600) {
            currentX = -300;
        }
        if (currentX < -300) {
            currentX = 1600;
        }

        DrawTexturePro(
            knightSheet,
            Rectangle{ frameWidth * frame, currentAnimation.animationHeight, currentFrameWidth, frameHeight },
            Rectangle{ currentX, currentY, frameWidth * 5, frameHeight * 5},
            Vector2{frameWidth / 2, frameHeight / 2},
            0.f,
            WHITE);

        EndDrawing();

    }

    UnloadTexture(knightSheet);

}