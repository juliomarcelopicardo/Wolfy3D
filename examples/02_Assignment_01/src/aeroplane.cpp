//*********************************************************************************************
// File:			Aeroplane.cpp
// Description:		A very simple class to represent an aeroplane as one object with all the
//					hierarchical components stored internally within the class.
// Module:			Real-Time 3D Techniques for Games
// Created:			Jake - 2010-2011
// Notes:
//*********************************************************************************************

#include "aeroplane.h"
#include "SilverLynx/globals.h"

Aeroplane::Aeroplane(float fX, float fY, float fZ, float fRotY) {
// 	m_mWorldMatrix = XMMatrixIdentity();
// 	m_mPropWorldMatrix = XMMatrixIdentity();
// 	m_mTurretWorldMatrix = XMMatrixIdentity();
// 	m_mGunWorldMatrix = XMMatrixIdentity();
// 	m_mCamWorldMatrix = XMMatrixIdentity();
// 
// 	m_v4Rot = XMFLOAT4(0.0f, fRotY, 0.0f, 0.0f);
// 	m_v4Pos = XMFLOAT4(fX, fY, fZ, 0.0f);
// 
// 	m_v4PropOff = XMFLOAT4(0.0f, 0.0f, 1.9f, 0.0f);
// 	m_v4PropRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
// 
// 	m_v4TurretOff = XMFLOAT4(0.0f, 1.05f, -1.3f, 0.0f);
// 	m_v4TurretRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
// 
// 	m_v4GunOff = XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f);
// 	m_v4GunRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
// 
// 	m_v4CamOff = XMFLOAT4(0.0f, 4.5f, -15.0f, 0.0f);
// 	m_v4CamRot = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
// 
// 	m_vCamWorldPos = XMVectorZero();
// 	m_vForwardVector = XMVectorZero();
// 
// 	m_fSpeed = 0.0f;
// 
// 	m_bGunCam = false;
// 
// 	m_bMoveUp = false;
// 	m_bMoveDown = false;
// 	m_bMoveLeft = false;
// 	m_bMoveRight = false;
// 
// 	////////////////////////////
// 	// Bullet
// 	bullet_position_ = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
// 	shoot_ = false;
// 
// 	Bullet b;
// 	b.position = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
// 	b.shot = false;
// 	b.mesh = NULL;
// 	bullets_.resize(kNumberOfBullets);
// 	std::fill(bullets_.begin(), bullets_.end(), b);
// 
// 	for (int i = 0; i < bullets_.size(); i++) {
// 		bullets_[i].mesh = CommonMesh::LoadFromXFile(Application::s_pApp, "Resources/Components/bullet.x");
// 	}
}

Aeroplane::~Aeroplane(void) {

}

void Aeroplane::SetWorldPosition(float fX, float fY, float fZ)
{
	//m_v4Pos = XMFLOAT4(fX, fY, fZ, 0.0f);
	update_matrices();
}

void Aeroplane::Shoot() {

}

SLX::Object Aeroplane::root() {
  return plane_root_;
}

void Aeroplane::update_matrices() {
  DirectX::XMMATRIX mRotX, mRotY, mRotZ, mTrans;
  DirectX::XMMATRIX mPlaneCameraRot, mForwardMatrix;
 
	// [START HERE]
	
	// Calculate m_mWorldMatrix for plane based on Euler rotation angles and position data.
	// i.e. Use XMMatrixRotationX(), XMMatrixRotationY(), XMMatrixRotationZ() and XMMatrixTranslationFromVector to calculate mRotX, mRotY, mRotZ and mTrans from m_v4Rot
	// Then concatenate the matrices to calculate m_mWorldMatrix
	mRotX = DirectX::XMMatrixRotationX(rotation_.x);
	mRotY = DirectX::XMMatrixRotationY(rotation_.y);
	mRotZ = DirectX::XMMatrixRotationZ(rotation_.z);
	mTrans = DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&position_));
	m_mWorldMatrix = mRotZ * mRotX * mRotY * mTrans;

	// [Skip this step first time through] Also calculate mPlaneCameraRot which ignores rotations in Z and X for the camera to parent to
	mPlaneCameraRot = DirectX::XMMatrixRotationY(rotation_.y);

	// [Skip this step first time through] Get the forward vector out of the world matrix and put it in m_vForwardVector
	DirectX::XMFLOAT4 fwd = { 0.0f, 0.0f, 1.0f, 0.0f };
	forward_ = DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&fwd), m_mWorldMatrix);

	// Calculate m_mPropWorldMatrix for propeller based on Euler rotation angles and position data.
	// Parent the propeller to the plane
	mRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_v4PropRot.x));
	mRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_v4PropRot.y));
	mRotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_v4PropRot.z));
	m_mPropWorldMatrix = mRotX * mRotY * mRotZ * DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4PropOff)) * m_mWorldMatrix;

	// Calculate m_mTurretWorldMatrix for propeller based on Euler rotation angles and position data.
	// Parent the turret to the plane
	mRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_v4TurretRot.x));
	mRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_v4TurretRot.y));
	mRotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_v4TurretRot.z));
	m_mTurretWorldMatrix = mRotX * mRotY * mRotZ * DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4TurretOff)) * m_mWorldMatrix;

	// Calculate m_mGunWorldMatrix for gun based on Euler rotation angles and position data.
	// Parent the gun to the turret
	mRotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_v4GunRot.x));
	mRotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_v4GunRot.y));
	mRotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_v4GunRot.z));
	m_mGunWorldMatrix = mRotX * mRotY * mRotZ * DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4GunOff)) * m_mTurretWorldMatrix;

	// Calculate m_mCameraWorldMatrix for camera based on Eculer rotation angles and position data.
	DirectX::XMFLOAT4 gun_positiond = { 15.0f, 10.0f, 5.0f, 0.0f };
	mRotX = DirectX::XMMatrixRotationX(m_v4CamRot.x);
	mRotY = DirectX::XMMatrixRotationY(m_v4CamRot.y);
	mRotZ = DirectX::XMMatrixRotationZ(m_v4CamRot.z);
	m_mCamWorldMatrix = (mRotX * mRotY * mRotZ * DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4CamOff))) * mPlaneCameraRot * mTrans;

	// [Skip this step first time through] Switch between parenting the camera to the plane (without X and Z rotations) and the gun based on m_bGunCam
	if (m_bGunCam) {
		m_mCamWorldMatrix = (mRotX * mRotY * mRotZ * DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&m_v4CamOff))) * m_mGunWorldMatrix;
	}

	// Get the camera's world position (m_vCamWorldPos) out of m_mCameraWorldMatrix
	DirectX::XMVECTOR quat, scale;
	DirectX::XMMatrixDecompose(&scale, &quat, &m_vCamWorldPos, m_mCamWorldMatrix);

	/////////////////////////////////////////
	// Bullets

// 	DirectX::XMMATRIX mBulletTrans;
// 	// bullet_position_.z = 5.0f;
// 	mBulletTrans = DirectX::XMMatrixTranslationFromVector(XMLoadFloat4(&bullet_position_));
// 	DirectX::XMFLOAT4 fwde = { 0.0f, 0.0f, 1.0f, 0.0f };
// 	
// 
// 	m_mBulletWorldMatrix = m_mGunWorldMatrix * mBulletTrans;
// 	//bullet_shot_rotation_x_ = DirectX::XMMatrixRotationX(m_v4GunRot.x);
// 	//bullet_shot_rotation_y_ = DirectX::XMMatrixRotationY(m_v4GunRot.y);
// 	//bullet_shot_rotation_z_ = DirectX::XMMatrixRotationZ(m_v4GunRot.z);
// 	bullet_shot_direction_ = m_mGunWorldMatrix * mBulletTrans;
// 
// 	DirectX::XMMatrixDecompose(&a, &b, &c, m_mGunWorldMatrix);
// 
// 	if (!shoot_) {
// 
// 		bullet_shot_direction_ = m_mGunWorldMatrix * mBulletTrans;
// 		m_mBulletWorldMatrix = m_mGunWorldMatrix * mBulletTrans;
// 		bullet_forward_ = DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&fwde), m_mGunWorldMatrix);
// 	}
// 	else {
// 		m_mBulletWorldMatrix = bullet_shot_direction_ * mBulletTrans;
// 	}

}

void Aeroplane::init(void) {
	// Init geometry resources
	geo_plane_.initFromFile("./../data/geometries/plane/plane.x");
	geo_prop_.initFromFile("./../data/geometries/plane/prop.x");
	geo_turret_.initFromFile("./../data/geometries/plane/turret.x");
	geo_gun_.initFromFile("./../data/geometries/plane/gun.x");

  mat_.init();

	// Initialize Aeroplane components
	plane_root_.addComponent(SLX::ComponentType::Transform);
	plane_root_.init();
	
	camera_node_.addComponent(SLX::ComponentType::Transform);
	camera_node_.init();
	camera_node_.transform_->set_position(0.0f, 4.5f, -15.0f);
	plane_root_.addChild(&camera_node_);

	plane_.addComponent(SLX::ComponentType::Transform);
	plane_.addComponent(SLX::ComponentType::Render3D);
	plane_.render3D_->setup(&mat_, &geo_plane_);
	plane_.render3D_->init();
	plane_.init();
	plane_root_.addChild(&plane_);

	prop_.addComponent(SLX::ComponentType::Transform);
	prop_.addComponent(SLX::ComponentType::Render3D);
	prop_.render3D_->setup(&mat_, &geo_prop_);
	prop_.render3D_->init();
	prop_.init();
	prop_.transform_->set_position(0.0f, 0.0f, 1.9f);
	plane_.addChild(&prop_);

  turret_.addComponent(SLX::ComponentType::Transform);
  turret_.addComponent(SLX::ComponentType::Render3D);
  turret_.render3D_->setup(&mat_, &geo_turret_);
  turret_.render3D_->init();
  turret_.init();
  turret_.transform_->set_position(0.0f, 1.05f, -1.3f);
  plane_.addChild(&turret_);

  gun_.addComponent(SLX::ComponentType::Transform);
  gun_.addComponent(SLX::ComponentType::Render3D);
  gun_.render3D_->setup(&mat_, &geo_gun_);
  gun_.render3D_->init();
  gun_.init();
  gun_.transform_->set_position(0.0f, 0.5f, 0.0f);
  turret_.addChild(&gun_);
}
