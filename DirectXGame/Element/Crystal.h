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

private:
    Fbx* crystalObj = nullptr;
    Fbx* circleObj = nullptr;

    float circleRot = 0;

    float rot = 0;
};

