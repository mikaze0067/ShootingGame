#pragma once
#include <KamataEngine.h>
#include "MathUtilityForText.h"
#include "PlayerBullet.h"
#include "Model2.h"

class Player {
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model2* model, uint32_t textureHandle);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(KamataEngine::Camera& camera_);

	void Attack();

	~Player();

	//ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	bool IsFinished() const { return finished_; }


private:

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model2* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	KamataEngine::Input* input_ = nullptr;
	//弾
	std::list<PlayerBullet*> bullets_;

	bool finished_ = false;

	// 連射間隔（フレーム数）
	const int kShotInterval_ = 5; // ← 5フレームごとに弾を出す（60fpsなら約0.083秒間隔）

	int shotTimer_ = 0;

};