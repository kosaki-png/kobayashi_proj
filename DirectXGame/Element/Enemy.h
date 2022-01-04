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

    /// <summary>
    /// 敵配置
    /// </summary>
    void Placement();

private:
    /// <summary>
    /// 当たり判定から向き変更
    /// </summary>
    /// <param name="dir">現在の向き</param>
    /// <returns>変更後の向き</returns>
    TexCollision::Dir DecMoveDir(TexCollision::Dir dir);

private: // メンバ変数
    Fbx* enemyObj = nullptr;
    XMFLOAT3 position = { 10,10,10 };
    XMFLOAT3 move = { 0,0,0 };

    float speed = 2.0f;
    bool canMove = true;

    TexCollision::Dir dir = TexCollision::Dir::Up;   // 最初の向き
    const int LENGTH = 3;   // 移動判定の幅

    int count = 0;
    const int CHANGEDIR_STOP = 0;   // 方向変更時の停止時間

    bool tracking = false;
};