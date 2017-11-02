#ifndef AEROPLANE_H
#define AEROPLANE_H

//*********************************************************************************************
// File:			Aeroplane.h
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include <vector>
#include "core/geometry.h"
#include "silverlynx.h"
#include "core/core.h"

__declspec(align(16)) class Aeroplane
{
  public:
	Aeroplane(float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f, float fRotY = 0.0f);
	~Aeroplane();

	void init(); // Only load the resources once for all instances

	void SetWorldPosition(float fX, float fY, float fZ);

	void Shoot();

	bool m_bMoveUp;
	bool m_bMoveDown;
	bool m_bMoveLeft;
	bool m_bMoveRight;

	bool shoot_;

	const int kNumberOfBullets = 10;

	struct Bullet {
		DirectX::XMFLOAT4 position;
		DirectX::XMVECTOR forward;
		DirectX::XMMATRIX orientation_matrix;
		DirectX::XMMATRIX world_matrix;
		SLX::CoreGeometry mesh;
		bool shot;
	};

  SLX::Object root();

  public:
	void update_matrices();

	SLX::CoreGeometry geo_plane_;
	SLX::CoreGeometry geo_prop_;
	SLX::CoreGeometry geo_turret_;
	SLX::CoreGeometry geo_gun_;

	SLX::Object plane_root_;
	SLX::Object plane_;
	SLX::Object prop_;
	SLX::Object turret_;
	SLX::Object gun_;

	SLX::CoreMaterial mat_;
	SLX::Object camera_node_;

	static bool s_bResourcesReady;
	std::vector<Bullet> bullets_;

	const float kPitchAcceleration = 3.0f;
	const float kPitchDecceleration = 3.0f;
	const float kRollAcceleration = 2.0f;
	const float kRollDecceleration = 2.0f;

	/////////////////////////////////////
	// Plane

	DirectX::XMFLOAT4 rotation_; // Euler rotation angles
	DirectX::XMFLOAT4 position_; // World position
	DirectX::XMVECTOR forward_; // Forward Vector for Plane
	float speed_; // Forward speed

	DirectX::XMMATRIX m_mWorldTrans; // World translation matrix
	DirectX::XMMATRIX m_mWorldMatrix; // World transformation matrix

	DirectX::XMFLOAT4 m_v4BulletRot; // Local rotation angles
	DirectX::XMFLOAT4 m_v4BulletOff; // Local offset
	DirectX::XMMATRIX m_mBulletWorldMatrix;

	DirectX::XMFLOAT4 m_v4PropRot; // Local rotation angles
	DirectX::XMFLOAT4 m_v4PropOff; // Local offset
	DirectX::XMMATRIX m_mPropWorldMatrix; // Propeller's world transformation matrix

	DirectX::XMFLOAT4 m_v4TurretRot; // Local rotation angles
	DirectX::XMFLOAT4 m_v4TurretOff; // Local offset
	DirectX::XMMATRIX m_mTurretWorldMatrix; // Turret's world transformation matrix

	DirectX::XMFLOAT4 m_v4GunRot; // Local rotation angles
	DirectX::XMFLOAT4 m_v4GunOff; // Local offset
	DirectX::XMMATRIX m_mGunWorldMatrix; // Gun's world transformation matrix

	DirectX::XMFLOAT4 m_v4CamRot; // Local rotation angles
	DirectX::XMFLOAT4 m_v4CamOff; // Local offset

	DirectX::XMVECTOR m_vCamWorldPos; // World position
	DirectX::XMMATRIX m_mCamWorldMatrix; // Camera's world transformation matrix

	bool m_bGunCam;

  public:
	float GetXPosition(void) { return position_.x; }
	float GetYPosition(void) { return position_.y; }
	float GetZPosition(void) { return position_.z; }
	DirectX::XMFLOAT4 GetFocusPosition(void) { return GetPosition(); }
	DirectX::XMFLOAT4 GetCameraPosition(void)
	{
		DirectX::XMFLOAT4 v4Pos;
		XMStoreFloat4(&v4Pos, m_vCamWorldPos);
		return v4Pos;
	}
	DirectX::XMFLOAT4 GetPosition(void) { return position_; }
	void SetGunCamera(bool value) { m_bGunCam = value; }

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

#endif