#pragma once
#include <KamataEngine.h>


KamataEngine::Matrix4x4 Multiply(KamataEngine::Matrix4x4 matrix1, KamataEngine::Matrix4x4 matrix2);

// 拡大縮小行列
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);

// 平行移動行列
KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translate);

// X
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);
// Y
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);
// Z
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

// 3次元アフィン変換行列
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translation);

KamataEngine::Vector3 Transform(const KamataEngine::Vector3& vector, const KamataEngine::Matrix4x4& matrix);

KamataEngine::Vector3 TransformNormal(const KamataEngine::Vector3& v, const KamataEngine::Matrix4x4& m);