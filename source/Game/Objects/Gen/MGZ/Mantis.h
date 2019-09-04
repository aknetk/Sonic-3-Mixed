#ifndef MANTIS_H
#define MANTIS_H

class Mantis;

#include <Utils/Standard.h>

#include <Engine/IApp.h>
#include <Engine/ISprite.h>

#include <Game/Object.h>
#include <Game/LevelScene.h>
#include <Game/Objects/Gen/ObjectListing.h>

class Mantis: public Enemy {
public:    
    
    int StartYpos;
    bool wentUp;
    
    void Create();
    int OnHit();
    void Update();
    void Render(int CamX, int CamY);
};

#endif /* MANTIS_H */
