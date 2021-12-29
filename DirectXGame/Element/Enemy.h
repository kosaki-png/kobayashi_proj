#pragma once
#include "Object.h"

class Enemy : public Object
{
private:
    enum Dir
    {
        Up,
        Down,
        Right,
        Left
    };

public: // �����o�֐�
    Enemy();
    ~Enemy();

    void Initialize(Input* input, TexCollision* texCol) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    XMFLOAT3 GetPosition() { return position; }
    void SetPosition(XMFLOAT3 position) { this->position = position; }

    Dir DecMoveDir(Dir dir);

private: // �����o�ϐ�
    Fbx* enemyObj = nullptr;
    XMFLOAT3 position = { 10,10,10 };
    XMFLOAT3 move = { 0,0,0 };

    float speed = 0;
    bool isMove = false;

    // ���x�ݒ�p
    float sence = 1.0f;

    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    bool canUp = true;
    bool canDown = true;
    bool canRight = true;
    bool canLeft = true;

    Dir dir = Up;

    const int LENGTH = 3;
};