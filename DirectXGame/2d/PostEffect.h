#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
private: // �G�C���A�X
   // Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::���ȗ�
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMMATRIX = DirectX::XMMATRIX;

    /// <summary>
    /// �萔�o�b�t�@�p�f�[�^�\����
    /// </summary>
    struct ConstBufferData
    {
        XMFLOAT4 color;	// �F (RGBA)
        XMMATRIX mat;	// �R�c�ϊ��s��
        float iTime;
        bool isGodray;
    };

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PostEffect();

    /// <summary>
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �`��R�}���h�̔��s
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �`��R�}���h�̔��s
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �`��R�}���h�̔��s
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGraphicsPipelineState();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="_"></param>
    void SetGodray(bool _) { isGodray = _; }

public:
    // �e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff[2];
    // SRV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;

    // �[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    // RTV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    // DSV�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;

    // �O���t�B�b�N�X�p�C�v���C��
    ComPtr<ID3D12PipelineState> pipelineState;
    // ���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootSignature;

private:
    // ��ʃN���A�J���[
    static const float clearColor[4];
    // �X�^�[�g���Ă���̎���
    float iTime = 0;

    bool isGodray = false;
};

