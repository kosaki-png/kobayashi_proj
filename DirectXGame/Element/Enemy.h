#pragma once
#include "Object.h"

class Enemy : public Object
{
public: // メンバ関数
    Enemy();
    ~Enemy();

    void Initialize(Input* input, TexCollision* texCol) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;
    void SpriteDraw() override;

    // 追尾用
    void SetTrack(bool isTrack) { tracking = isTrack; }
    bool GetTrack() { return tracking; }

private:
    /// <summary>
    /// 当たり判定から向き変更
    /// </summary>
    /// <param name="dir">現在の向き</param>
    /// <returns>変更後の向き</returns>
    TexCollision::Dir DecMoveDir(TexCollision::Dir dir);

private: // メンバ変数
    Fbx* enemyObj = nullptr;
    Fbx* circleObj = nullptr;

    XMFLOAT3 move = { 0,0,0 };

    const float speedLow = 0.3f;
    const float speedHigh = 0.8f;
    bool canMove = true;

    TexCollision::Dir dir = TexCollision::Dir::Up;   // 最初の向き
    const int LENGTH = 3;   // 移動判定の幅

    int stopCnt = 0;
    const int CHANGEDIR_STOP = 60;   // 方向変更時の停止時間

    bool tracking = false;
};