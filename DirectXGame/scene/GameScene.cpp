#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Green.png");
	textureHandleEnemy_ = TextureManager::Load("Blue.png");

	// 3Dモデルの生成
	model_ = Model2::Create();
	modelEnemy_ = Model2::Create();
	modelSkydome_ = Model2::CreateFromOBJ("sphere", true);

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	camera_.Initialize();

	// DirectX初期化などの前に
	Model2::StaticInitialize();
	
	//// ゲーム起動処理
	//gameScene = new GameScene();
	//gameScene->Initialize();

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_,textureHandle_);

	// 敵キャラの生成
	enemy_ = new Enemy();
	// 敵キャラの初期化
	enemy_->Initialize(modelEnemy_, textureHandleEnemy_);

	//天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_, &camera_);

	soundDataHandle_ = audio_->LoadWave("maou_bgm_ethnic32.mp3");
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);


	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetCamera(&camera_);
}

void GameScene::Update() {

	// カメラ設定（少し上から見下ろす）
	camera_.translation_ = {0.0f, 40.0f, -10.0f};
	camera_.rotation_ = {1.0f, 0.0f, 0.0f};
	camera_.UpdateMatrix();

	// 天球の更新
	skydome_->Update();
	// 自キャラの更新
	player_->Update();

	// 敵キャラの更新
	enemy_->Update();

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	CheckAllCollisions();

	if (finished_ == true) {
		audio_->StopWave(voiceHandle_);
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	dxCommon_ = DirectXCommon::GetInstance();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(dxCommon_->GetCommandList());

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model2::PreDraw(dxCommon_->GetCommandList());

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 天球の描画
	skydome_->Draw();

	//自キャラの描画
	player_->Draw(camera_);

	// 敵キャラの描画
	enemy_->Draw(camera_);

	// 3Dオブジェクト描画後処理
	Model2::PostDraw();
#pragma endregion

}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();
		// 球と球の交差判定
		if (((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z) <= (1.0f + 1.0f) * (1.0f + 1.0f))) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->IsFinished();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラの座標
	posB = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {
		// 自弾の座標
		posA = bullet->GetWorldPosition();
		// 球と球の交差判定
		if (((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z) <= (1.0f + 1.0f) * (1.0f + 1.0f))) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	/*for (PlayerBullet* bulletP : playerBullets) {
		// 自弾の座標
		posA = bulletP->GetWorldPosition();
		for (EnemyBullet* bulletE : enemyBullets) {
			// 敵弾の座標
			posB = bulletE->GetWorldPosition();
			// 球と球の交差判定
			if (((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z) <= (1.0f + 1.0f) * (1.0f + 1.0f))) {
				// 自弾の衝突時コールバックを呼び出す
				bulletP->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				bulletE->OnCollision();
			}
		}
	}*/
#pragma endregion
}
