#pragma once

#include "Particle3D.h"

class Gush : public Particle3D
{
private:
    struct Cube
    {
        Fbx* cubeObj = nullptr;
        XMFLOAT3 cubePos = { 0,0,0 };
        XMFLOAT3 rotSpeed = { 0,0,0 };
        XMFLOAT3 cubeScale = { 1,1,1 };
    };

public:
    Gush();
    ~Gush();

    void Initialize() override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    void SetPlayerPos(XMFLOAT3 playerPos) { this->playerPos = playerPos; }

    /// <summary>
    /// ”z’u
    /// </summary>
    void Placement();

private:
    XMFLOAT3 playerPos = { 0,0,0 };

    static const int CUBE_COUNT = 4;
    Cube cube[CUBE_COUNT];
};

