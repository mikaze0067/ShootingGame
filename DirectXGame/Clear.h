#pragma once
#include <KamataEngine.h>
#include "Model2.h"



class ClearScene {
public:
	~ClearScene();
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
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransformTitle_;
	KamataEngine::WorldTransform worldTransformPlayer_;


	KamataEngine::Model2* model_ = nullptr;

	float counter_ = 0.0f;
	// 終了フラグ
	bool finished_ = false;
	static inline const float kTimeTitleMove = 2.0f;

	int time = 360;

	
	//
	uint32_t texture;
	KamataEngine::Sprite* sprite = nullptr;
	
};