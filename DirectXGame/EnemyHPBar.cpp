#include "EnemyHpBar.h"
#include "Enemy.h"

using namespace KamataEngine;

void EnemyHpBar::Initialize() {
	uint32_t tex = TextureManager::Load("white.png");
	back_ = Sprite::Create(tex, {0, 0});
	front_ = Sprite::Create(tex, {0, 0});
}

void EnemyHpBar::Draw(const Enemy* enemy, const Camera& camera) {
	if (!enemy) {
		return;
	}

	Vector3 pos = enemy->GetWorldPosition();

	float ratio = enemy->GetHpRatio();

	back_->SetPosition({25, 40});
	back_->SetSize({50, 6});
	back_->SetColor(Vector4(0, 0, 0, 1));

	front_->SetPosition({25, 40});
	front_->SetSize({50 * ratio, 6});
	front_->SetColor(Vector4(1, 0, 0, 1));

	back_->Draw();
	front_->Draw();
}
