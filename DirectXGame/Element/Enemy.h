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

    /// <summary>
    /// �G�z�u
    /// </summary>
    void Placement();

private:
    /// <summary>
    /// �����蔻�肩������ύX
    /// </summary>
    /// <param name="dir">���݂̌���</param>
    /// <returns>�ύX��̌���</returns>
    TexCollision::Dir DecMoveDir(TexCollision::Dir dir);

private: // �����o�ϐ�
    Fbx* enemyObj = nullptr;
    XMFLOAT3 position = { 10,10,10 };
    XMFLOAT3 move = { 0,0,0 };

    float speed = 2.0f;
    bool canMove = true;

    TexCollision::Dir dir = TexCollision::Dir::Up;   // �ŏ��̌���
    const int LENGTH = 3;   // �ړ�����̕�

    int count = 0;
    const int CHANGEDIR_STOP = 0;   // �����ύX���̒�~����

    bool tracking = false;
};