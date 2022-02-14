#pragma once

#include "Particle3D.h"
#include <random>

class Gush : public Particle3D
{
private:
    struct GushObj
    {
        Fbx* cubeObj = nullptr;
        XMFLOAT3 cubePos = { 0,0,0 };
        XMFLOAT3 cubeScale = { 1,1,1 };
    };

public:
    Gush();
    ~Gush();

    void Initialize() override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    void SetPlayerPos(XMFLOAT3 playerPos) { this->playerPos = playerPos; }

    void SetDis(XMFLOAT2 dis) { distance = dis; }
    void SetMax(float max) { this->max = max; }
    void SetSpeed(float speed) { this->speed = speed; }

    /// <summary>
    /// îzíu
    /// </summary>
    void Placement();

private:
    XMFLOAT3 playerPos = { 0,0,0 };

    GushObj cube;

    XMFLOAT2 distance = { -5,0 };    // ñAÇÃèoÇÈä‘äu
    float max = 10.0f;
    float speed = 0.075f;
};

