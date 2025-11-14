#include "PlayerBullet.h"
#include "MathUtilityForText.h"
#include <cassert>

using namespace KamataEngine;

void PlayerBullet::Initialize(Model2* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("Red.png");

	// ワールド変換の初期化
	worldTransform_.Initialize();
	// 弾のサイズを小さくする
	worldTransform_.scale_ = {0.3f, 0.3f, 0.3f}; // ← 数字を小さくすると弾が小さくなる
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() {

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	//座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;

	// ワールド変換の更新
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const Camera& camera) { model_->Draw(worldTransform_, camera, textureHandle_); }

void PlayerBullet::OnCollision() { isDead_ = true; }

Vector3 PlayerBullet::GetWorldPosition() {
	/// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;
	return worldPos;
}
