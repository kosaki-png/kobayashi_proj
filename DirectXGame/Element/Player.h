#pragma once
#include <iostream>

#include "Object.h"

class Player : public Object
{
public: // �����o�֐�
    Player(int window_width, int window_height);
    ~Player();

    void Initialize(Input* input, TexCollision* texCol) override;
    void Update() override;
    void Draw(ID3D12GraphicsCommandList* cmdList) override;

    /// <summary>
    /// �ړ��ʐݒ�
    /// </summary>
    /// <returns></returns>
    XMFLOAT3 GetMove() { return move; }

    /// <summary>
    /// �ړ��ʐݒ�
    /// </summary>
    /// <returns></returns>
    void Setmove(XMFLOAT3 move) { this->move = move; }

    // ���x�ύX
    void SetSence(float sence);
    float GetSence() { return sence; }

private: // �����o�ϐ�
    float scaleX = 1.0f;
    float scaleY = 1.0f;

    Fbx* playerObj = nullptr;
    XMFLOAT3 move = { 0,0,0 };

    float cameraTheta = 0;
    float cameraPhi = 90;

    float cameraAngleX = 0;	// rad
    float cameraAngleY = 0;	// rad

    float speed = 0;

    // ���x�ݒ�p
    float sence = 1.0f;

    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;
};