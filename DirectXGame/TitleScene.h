#pragma once

#include <KamataEngine.h>
#include "IScene.h"
#include "Model2.h"


class TitleScene : public IScene {
public:

	~TitleScene() override;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
	// デスフラグのgetter
	bool IsFinished() const override { return finished_; }

	SceneType GetNextScene() const override { return SceneType::kGame; }

private:

	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransformTitle_;
	KamataEngine::WorldTransform worldTransformPlayer_;

	KamataEngine::Model2* model_ = nullptr;

	float counter_ = 0.0f;
	// 終了フラグ
	bool finished_ = false;
	static inline const float kTimeTitleMove = 2.0f;

	uint32_t textureHandle_ = 0;
	KamataEngine::Sprite* sprite_ = nullptr;
};
