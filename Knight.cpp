//
// Created by 307022419 on 1/6/2025.
//

#include "Knight.h"
#include "raylib.h"

Knight::Knight() {
    knightSheet = LoadTexture("knight_sheet.png");

    //dimensions of a singular frame
    frameWidth = static_cast<float>(knightSheet.width) / 12;
    frameHeight = static_cast<float>(knightSheet.height) / 30;

    //flips knight animation when moving backwards
    currentFrameWidth = frameWidth;
    flippedFrameWidth = -frameWidth;

    //timer
    timer = 0.f;
    timePerFrame = .12;

    //frames
    frame = 0;

    //animation structs
    attackAnimation.animationHeight = 0;
    attackAnimation.maxFrames = 4;

    attack2Animation.animationHeight = knightSheet.height - (frameHeight * 28);
    attack2Animation.maxFrames = 6;

    idleAnimation.animationHeight = knightSheet.height - (frameHeight * 14);
    idleAnimation.maxFrames = 10;

    jumpAnimation.animationHeight = knightSheet.height - (frameHeight * 13);
    jumpAnimation.maxFrames = 3;

    crouchAnimation.animationHeight = knightSheet.height - (frameHeight * 20);
    crouchAnimation.maxFrames = 1;

    crouch_walkAnimation.animationHeight = knightSheet.height - (frameHeight * 20);
    crouch_walkAnimation.maxFrames = 8;

    runAnimation.animationHeight = knightSheet.height - (frameHeight * 10);
    runAnimation.maxFrames = 10;

    //holds current animation
    currentAnimation.maxFrames = 10;

    //position
    float currentX = 0;
    float currentY = 300;

    //jump physics
    float gravity = 500;
    float velocityY = 0;
}

void Knight::drawKnight() {

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
    }