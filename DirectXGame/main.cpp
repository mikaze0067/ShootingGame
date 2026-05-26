#include "KamataEngine.h"
#include <Windows.h>
#include <memory>
#include "scene/GameScene.h"
#include "TitleScene.h"
#include "Clear.h"
#include "IScene.h"

using namespace KamataEngine;

std::unique_ptr<IScene> currentScene = nullptr;

void ChangeScene();

void UpdateScene();

void DrawScene();

std::unique_ptr<IScene> CreateScene(SceneType sceneType) {
	std::unique_ptr<IScene> newScene = nullptr;

	switch (sceneType) {
	case SceneType::kTitle:
		newScene = std::make_unique<TitleScene>();
		break;
	case SceneType::kGame:
		newScene = std::make_unique<GameScene>();
		break;
	case SceneType::kClear:
		newScene = std::make_unique<ClearScene>();
		break;
	}

	newScene->Initialize();
	return newScene;
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
// エンジン初期化
	KamataEngine::Initialize(L"LE4D_09_ササノ_ミカゼ");

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// 最初のシーンの初期化
	currentScene = CreateScene(SceneType::kTitle);

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
	currentScene.reset();

	// 3Dモデル解放
	Model2::StaticFinalize();
	return 0;
}

void ChangeScene() {
	if (currentScene && currentScene->IsFinished()) {
		currentScene = CreateScene(currentScene->GetNextScene());
	}
}

void UpdateScene() {
	if (currentScene) {
		currentScene->Update();
	}
}

void DrawScene() {
	if (currentScene) {
		currentScene->Draw();
	}
}
