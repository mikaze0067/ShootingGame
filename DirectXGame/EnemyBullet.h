#pragma once
#include <KamataEngine.h>
#include "Model2.h"

class EnemyBullet {
public: // メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model2* model, const KamataEngine::Vector3& posision, const KamataEngine::Vector3& velocity);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const KamataEngine::Camera& camera);

	bool IsDead() const { return isDead_; }

	static const int32_t kLifeTime = 60 * 5;

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision();

	KamataEngine::Vector3 GetWorldPosition();


private:

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// 3Dモデル
	KamataEngine::Model2* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	KamataEngine::Vector3 velocity_;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
};