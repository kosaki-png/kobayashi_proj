#pragma once
#include "Sprite.h"
class PostEffect :
    public Sprite
{
private: // エイリアス
   // Microsoft::WRL::を省略
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::を省略
    using XMFLOAT2 = DirectX::XMFLOAT2;
    using XMFLOAT3 = DirectX::XMFLOAT3;
    using XMFLOAT4 = DirectX::XMFLOAT4;
    using XMMATRIX = DirectX::XMMATRIX;

    /// <summary>
    /// 定数バッファ用データ構造体
    /// </summary>
    struct ConstBufferData
    {
        XMFLOAT4 color;	// 色 (RGBA)
        XMMATRIX mat;	// ３Ｄ変換行列
        float iTime;
        bool isGodray;
    };

public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PostEffect();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 描画コマンドの発行
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// 描画コマンドの発行
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// 描画コマンドの発行
    /// </summary>
    /// <param name="cmdList">コマンドリスト</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// パイプライン生成
    /// </summary>
    void CreateGraphicsPipelineState();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="_"></param>
    void SetGodray(bool _) { isGodray = _; }

public:
    // テクスチャバッファ
    ComPtr<ID3D12Resource> texBuff[2];
    // SRV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;

    // 深度バッファ
    ComPtr<ID3D12Resource> depthBuff;
    // RTV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    // DSV用デスクリプタヒープ
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;

    // グラフィックスパイプライン
    ComPtr<ID3D12PipelineState> pipelineState;
    // ルートシグネチャ
    ComPtr<ID3D12RootSignature> rootSignature;

private:
    // 画面クリアカラー
    static const float clearColor[4];
    // スタートしてからの時間
    float iTime = 0;

    bool isGodray = false;
};

