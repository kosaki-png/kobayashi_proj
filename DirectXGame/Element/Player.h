#pragma once
#include "Object.h"

class Player : public Object
{
public: // メンバ関数
    Player();
    ~Player();

    void Initialize(Input* input) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    XMFLOAT3 GetPosition() { return position; }

private: // メンバ変数
    Fbx* playerObj = nullptr;

    XMFLOAT3 position = { 0,0,0 };
    float fhita = 0;
    float phi = 0;
};