#include "KamataEngine.h"
#include <Windows.h>
#include "scene/GameScene.h"
#include "TitleScene.h"
#include "Clear.h"

using namespace KamataEngine;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;
ClearScene* clearScene = nullptr;

// シーン（型）
enum class Scene {
	kUnknown = 0,

	kTitle,
	kGame,
	kClear,
};
// 現在シーン（型）
Scene scene = Scene::kTitle;

void ChangeScene();

void UpdateScene();

void DrawScene();


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
// エンジン初期化
	KamataEngine::Initialize(L"LE3D_08_ササノ_ミカゼ_WP");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 最初のシーンの初期化
	scene = Scene::kTitle;

	// タイトルシーンの初期化
	titleScene = new TitleScene();
	titleScene->Initialize();

	// クリアシーン
	clearScene = new ClearScene();
	clearScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		// シーン切り替え
		ChangeScene();
		// 現在のシーン
		UpdateScene();
		//// ゲームシーンの毎フレーム処理
		//gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// 現在シーンの描画
		DrawScene();
		//// ゲームシーンの描画
		//gameScene->Draw();


		// 描画終了
		dxCommon->PostDraw();
	}

	// 各種解放
	delete gameScene;
	delete titleScene;

	// 3Dモデル解放
	Model2::StaticFinalize();
	return 0;
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新しいシーンの生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		if (gameScene->IsFinished()) {
			// シーン変更
			scene = Scene::kClear;
			// 旧シーンの解放
			delete gameScene;
			gameScene = nullptr;
			// 新しいシーンの生成と初期化
			clearScene = new ClearScene;
			clearScene->Initialize();
		}
		break;
	case Scene::kClear:
		if (clearScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete clearScene;
			clearScene = nullptr;
			// 新しいシーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	}
}

void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();

		break;
	case Scene::kGame:
		gameScene->Update();
		break;
	case Scene::kClear:
		clearScene->Update();
		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	case Scene::kClear:
		clearScene->Draw();
		break;
	}
}
