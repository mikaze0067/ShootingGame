#pragma once

enum class SceneType {
	kTitle,
	kGame,
	kClear,
};

class IScene {
public:
	virtual ~IScene() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool IsFinished() const = 0;
	virtual SceneType GetNextScene() const = 0;
};
