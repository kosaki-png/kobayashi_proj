#pragma once
#include <iostream>

#include "Object.h"

class Player : public Object
{
public: // メンバ関数
    Player(int window_width, int window_height);
    ~Player();

    void Initialize(Input* input, TexCollision* texCol) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;
    void SpriteDraw() override;
    void SetIsDead(bool isDead) override;

    /// <summary>
    /// 移動量設定
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetMove() { return move; }

    /// <summary>
    /// 移動量設定
    /// </summary>
    /// <returns></returns>
    void Setmove(XMFLOAT3 move) { this->move = move; }

    // 感度変更
    void SetSence(float sence);
    float GetSence() { return sence; }

    // 一番近いクリスタルとの角度取得
    void SetCrystalRad(float rad) { crystalRad = rad; }

private: // メンバ変数
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    Fbx* playerObj = nullptr;
    XMFLOAT3 move = { 0,0,0 };

    Fbx* arrowObj = nullptr;
    XMFLOAT3 arrowRot = { 0,0,0 };

    float cameraTheta = 0;
    float cameraPhi = 90;

    float cameraAngleX = 0;	// rad
    float cameraAngleY = 0;	// rad

    float speed = 0;

    // 感度設定用
    float sence = 1.0f;

    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    float crystalRad = 0;
};