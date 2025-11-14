#pragma once

#include <KamataEngine.h>
#include "../Player.h"
#include "../Skydome.h"
#include "../Enemy.h"
#include "../Model2.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

	// 3Dモデル
	KamataEngine::Model2* model_ = nullptr;
	KamataEngine::Model2* modelEnemy_ = nullptr;
	KamataEngine::Model2* modelSkydome_ = nullptr;
	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// ビュープロジェクション
	KamataEngine::Camera camera_;

private: // メンバ変数
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// テクスチャハンドル
	uint32_t textureHandleEnemy_ = 0;
	//自キャラ
	Player* player_ = nullptr;
	// 敵キャラ
	Enemy* enemy_ = nullptr;
	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	// 天球
	Skydome* skydome_ = nullptr;
	// 終了フラグ
	bool finished_ = false;

	uint32_t soundDataHandle_ = 0;

	uint32_t voiceHandle_ = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
