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
    void SpriteDraw() override;

    // �ǔ��p
    void SetTrack(bool isTrack) { tracking = isTrack; }
    bool GetTrack() { return tracking; }

private:
    /// <summary>
    /// �����蔻�肩������ύX
    /// </summary>
    /// <param name="dir">���݂̌���</param>
    /// <returns>�ύX��̌���</returns>
    TexCollision::Dir DecMoveDir(TexCollision::Dir dir);

private: // �����o�ϐ�
    Fbx* enemyObj = nullptr;
    Fbx* circleObj = nullptr;

    XMFLOAT3 move = { 0,0,0 };

    const float speedLow = 0.3f;
    const float speedHigh = 0.8f;
    bool canMove = true;

    TexCollision::Dir dir = TexCollision::Dir::Up;   // �ŏ��̌���
    const int LENGTH = 3;   // �ړ�����̕�

    int stopCnt = 0;
    const int CHANGEDIR_STOP = 60;   // �����ύX���̒�~����

    bool tracking = false;
};