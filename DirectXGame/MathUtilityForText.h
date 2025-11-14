#include <KamataEngine.h>
#include "Affine.h"
#include "AABB.h"

KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v);
KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v);

// 代入演算子オーバーロード
// Vector3の足算
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv);

KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv);

// 代入演算子オーバーロード
// Vector3の掛け算
KamataEngine::Vector3& operator*=(KamataEngine::Vector3& v, float s);

KamataEngine::Vector3& operator/=(KamataEngine::Vector3& v, float s);

// 2項演算子オーバーロード
// Vector3の足し算
const KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

const KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

// 2項演算子オーバーロード
// Vector3の掛け算
const KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float s);

const KamataEngine::Vector3 operator*(float s, const KamataEngine::Vector3& v);

const KamataEngine::Vector3 operator/(const KamataEngine::Vector3& v, float s);

float EaseInOut(float x1, float x2, float t);
float Lerp(float x1, float x2, float t);
KamataEngine::Vector3 Leap(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2, float t);

bool IsCollision(const AABB& aabb1, const AABB& aabb2);

KamataEngine::Matrix4x4 PlayerAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

float Dot(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

float Length(const KamataEngine::Vector3& v);

KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);

