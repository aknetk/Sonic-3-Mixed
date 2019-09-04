// Object ID: 0x81
// Object Name: EggCapsule.cpp

#include "EggCapsule.h"

typedef IMath Math;

CONSTRUCTER EggCapsule::EggCapsule() {
    if (SaveGame::CurrentMode == 0) {
        BinIndex = LevelScene::LoadSpriteBin("GlobalS3K/EggPrison.bin");
    }
    else {
        BinIndex = LevelScene::LoadSpriteBin("Global/EggPrison.bin");
    }
}

void EggCapsule::Create() {
    Object::Create();
    Active = true;
    Priority = true;
    Flying = FlipY;
    Solid = true;
    Scene->AddSelfToRegistry(this, "Solid");
    W = 64;
    H = 64;
    CurrentAnimation = Sprite->FindAnimation("Capsule");
    Broken = false;
    if (Flying) {
        MaxAccel = 0xC0;
        YSpeed = 0xC0;
        Acceleration = 0x10;
        SwingDirection = 0;
    }
    else {
        Gravity = 0x70;
    }
    Button = Scene->AddNewObject(Obj_EggCapsuleButton, 0, X, Y - 32, false, FlipY);
    Button->Sprite = Sprite;
    Button->CurrentAnimation = CurrentAnimation + 1;
    VisualLayer = 1;
}

void EggCapsule::Update() {
    if (!isHeldDebugObject) {
        if (Flying) {
            Swing_UpAndDown();
        }
        else {
            if (Gravity) {
                while (Scene->CollisionAt(X, Y + 32 + 1)) {
                    Y--;
                    YSpeed = 0;
                    Gravity = 0;
                }

                if (Gravity == 0) {
                    Y++;
                    Y++;
                    Sound::Play(Sound::SFX_IMPACT4);
                    Scene->ShakeTimer = 20;
                }

            }

        }
        Button->SubY = SubY + (YSpeed << 8) - 0x200000;
        Button->InitialY = Button->SubY >> 16;
        if (Button->BounceOffShield && !Broken) {
            Broken = true;
            Scene->StopTimer = true;
            Sound::Play(Sound::SFX_DESTROY);
            App->Audio->RemoveMusic(Sound::SoundBank[0xFD]);
            Scene->DoResults();
        }

    }

    Object::Update();
}

void EggCapsule::Render(int CamX, int CamY) {
    if (Flying) {
        G->DrawSprite(Sprite, CurrentAnimation + 3, Scene->Frame & 3, X - 20 - CamX, Y - 36 - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation + 3, Scene->Frame & 3, X + 20 - CamX, Y - 36 - CamY, 0, IE_NOFLIP);
        G->DrawSprite(Sprite, CurrentAnimation, Broken, X - CamX, Y - CamY, 0, IE_FLIPY);
    }
    else {
        G->DrawSprite(Sprite, CurrentAnimation, Broken, X - CamX, Y - CamY, 0, IE_NOFLIP);
    }
    }
