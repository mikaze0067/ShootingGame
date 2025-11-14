#pragma once
#include <KamataEngine.h>
#include "Model2.h"

class Skydome {
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model2* model, KamataEngine::Camera* camera);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	//モデル
	KamataEngine::Model2* model_ = nullptr;

};