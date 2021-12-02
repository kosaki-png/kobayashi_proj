#pragma once
#include "Object.h"
#include <DirectXMath.h>

class Player : public Object
{
public: // メンバ関数
    Player(int window_width, int window_height);
    ~Player();

    void Initialize(Input* input) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    XMFLOAT3 GetPosition() { return position; }
    void SetPosition(XMFLOAT3 position) { this->position = position; }

    //XMFLOAT3 GetRePosition() { return rePosition; }
    //void SetRePosition(XMFLOAT3 rePosition) { this->rePosition = rePosition; }

    XMFLOAT3 GetMove() { return move; }
    void Setmove(XMFLOAT3 move) { this->move = move; }

    // 感度変更
    void SetSence(float sence);
    float GetSence() { return sence; }

private: // メンバ変数
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    Fbx* playerObj = nullptr;
    XMFLOAT3 position = { 10,10,10 };
    //XMFLOAT3 rePosition = { 0,0,0 };
    XMFLOAT3 move = { 0,0,0 };

    float cameraTheta = 0;
    float cameraPhi = 90;

    float cameraAngleX = 0;	// rad
    float cameraAngleY = 0;	// rad

    float playerTheta = 0;
    float playerPhi = 0;

    float playerAngleX = 0;	// rad
    float playerAngleY = 0;	// rad

    float speed = 0;
    bool isMove = false;

    // 感度設定用
    float sence = 1.0f;

    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;
};