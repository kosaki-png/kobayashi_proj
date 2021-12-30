#pragma once
#include "Object.h"

class Enemy : public Object
{

public: // �����o�֐�
    Enemy();
    ~Enemy();

    void Initialize(Input* input, TexCollision* texCol) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    void Placement();

    XMFLOAT3 GetPosition() { return position; }
    void SetPosition(XMFLOAT3 position) { this->position = position; }

private:
    TexCollision::Dir DecMoveDir(TexCollision::Dir dir);

private: // �����o�ϐ�
    Fbx* enemyObj = nullptr;
    XMFLOAT3 position = { 10,10,10 };
    XMFLOAT3 move = { 0,0,0 };

    float speed = 2.0f;
    bool isMove = false;

    // ���x�ݒ�p
    float sence = 2.0f;

    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    bool canUp = true;
    bool canDown = true;
    bool canRight = true;
    bool canLeft = true;

    TexCollision::Dir dir = TexCollision::Dir::Up;
    const int LENGTH = 3;

    int count = 0;
    // �����ύX���̒�~����
    const int CHANGEDIR_STOP = 0;
    // �����ύX����
    const int CHANGEDIR = 0;

    bool canMove = true;
};