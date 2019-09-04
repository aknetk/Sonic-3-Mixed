// Object ID: 0xFFFFFFFF
// Object Name: AIZMinibossFlame.cpp

#include "AIZMinibossFlame.h"

typedef IMath Math;

void AIZMinibossFlame::Create() {
    Enemy::Create();
    Active = true;
    Priority = false;
    W = 32;
    H = 32;
    Frame = 0;
    TimerAction = 0;
    Timer = (6 - SubType) << 1;
}

int AIZMinibossFlame::OnHit() {
    return 0;
}

void AIZMinibossFlame::Update() {
    if (Timer == 0) {
        switch (TimerAction) {
            case 0:
            {
                Invincible = true;
                Harmful = true;
                NegatedByFireShield = true;
                TimerAction = 1;
                Timer = (6 - SubType) << 1;
                break;
            }
            case 1:
            {
                Active = false;
                break;
            }
        }

        Timer = -1;
    }

    Object::Update();
}

void AIZMinibossFlame::Render(int CamX, int CamY) {
    G->DrawSprite(Sprite, CurrentAnimation, 0, X - CamX, Y - CamY, 0, FlipX);
    }
