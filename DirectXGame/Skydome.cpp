#include "Skydome.h"

using namespace KamataEngine;

void Skydome::Initialize(Model2* model, Camera* camera) {
	worldTransform_.Initialize();
	model_ = model;
	camera_ = camera;
}

void Skydome::Update() {
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_);
}
