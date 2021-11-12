#pragma once
#include "Object.h"
#include <DirectXMath.h>

class Player : public Object
{
public: // ƒƒ“ƒoŠÖ”
    Player(int window_width, int window_height);
    ~Player();

    void Initialize(Input* input) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    XMFLOAT3 GetPosition() { return position; }
    void SetPosition(XMFLOAT3 position) { this->position = position; }

    XMFLOAT3 GetRePosition() { return rePosition; }
    void SetRePosition(XMFLOAT3 rePosition) { this->rePosition = rePosition; }

private: // ƒƒ“ƒo•Ï”
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    Fbx* playerObj = nullptr;
    XMFLOAT3 position = { 0,0,0 };
    XMFLOAT3 rePosition = { 0,0,0 };

    float theta = 0;
    float phi = 0;

    float angleX = 0;	// rad
    float angleY = 0;	// rad
};