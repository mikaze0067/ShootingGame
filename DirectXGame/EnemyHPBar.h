#pragma once
#include <KamataEngine.h>


class Enemy;

class EnemyHpBar {
public:
	void Initialize();

	void Draw(const Enemy* enemy, const KamataEngine::Camera& camera);


private:
	KamataEngine::Sprite* back_ = nullptr;

	KamataEngine::Sprite* front_ = nullptr;

};
