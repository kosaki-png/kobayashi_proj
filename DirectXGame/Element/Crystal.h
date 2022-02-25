#pragma once
#include "Object.h"

class Crystal : public Object
{
public:
    Crystal();
    ~Crystal();

    void Initialize(Input* input, TexCollision* texCol) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;
    void SpriteDraw() override;

    // é©ã@ÇÃèÍèäê›íË
    void SetPlayerPos(XMFLOAT3 position) { playerPos = position; }

    // ââèoíÜÇ©ÇÃéÊìæ
    bool GetIsEffect() { return isEffect; }

    void SetIsDead(bool isDead) override;

private:
    Fbx* crystalObj = nullptr;
    Fbx* circleObj = nullptr;
    Fbx* debri = nullptr;

    float circleRot = 0;

    float rot = 0;

    XMFLOAT3 playerPos = { 0,0,0 };

    XMFLOAT3 debriPos = { 0,0,0 };
    XMFLOAT3 debriRot = { 0,0,0 };
    float debriScale = 0;

    int debriCnt = 0;

    bool isEffect = false;
    int effectCnt = 0;
};

