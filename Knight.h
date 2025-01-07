//
// Created by 307022419 on 1/6/2025.
//

#ifndef KNIGHT_H
#define KNIGHT_H
#include "raylib.h"


class Knight {
public:
    Knight();
    void drawKnight();

    void moveRight();
    void moveLeft();
    void jump();
    void crouch();

private:
    Texture2D knightSheet{};

    float frameWidth;
    float frameHeight;

    float currentFrameWidth;
    float flippedFrameWidth;

    float timer;
    float timePerFrame;

    int frame;

    struct AnimationStruct {
        float animationHeight;
        int maxFrames;
    };

    AnimationStruct attackAnimation{};
    AnimationStruct attack2Animation{};
    AnimationStruct idleAnimation{};
    AnimationStruct jumpAnimation{};
    AnimationStruct crouchAnimation{};
    AnimationStruct crouch_walkAnimation{};
    AnimationStruct runAnimation{};
    AnimationStruct currentAnimation{};

    float currentX{};
    float currentY{};

    float gravity{};
    float velocityY{};

};



#endif //KNIGHT_H
