//
// Created by 307022419 on 1/6/2025.
//

#ifndef KNIGHT_H
#define KNIGHT_H
#include "raylib.h"


class Knight {
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

    bool isGrounded;
    bool isFlipped;

    bool animationPlaying;

public:
    Knight();

    void playAnimation(AnimationStruct);

    void drawKnight();



    void moveRight();
    void moveLeft();
    void jump();
    void crouch();



};



#endif //KNIGHT_H
