#pragma once

#include <Kinect.h>
#include <string>
using namespace std;

#include "defines.hpp"

	// left, right는 전면을 마주한 상태에서 카메라 기준 사용자를 바라보는 방향
	enum SPointsType {
		SPOINT_HEAD_TOP,
		SPOINT_HEAD_HAIR,
		SPOINT_HEAD_SIDE_LEFT,
		SPOINT_HEAD_SIDE_RIGHT,
		SPOINT_HEAD_FACE_EYE_LEFT,
		SPOINT_HEAD_FACE_EYE_RIGHT,
		SPOINT_HEAD_FACE_NOSE,
		SPOINT_HEAD_FACE_LIP,
		SPOINT_HEAD_FACE_CHEEK_LEFT,
		SPOINT_HEAD_FACE_CHEEK_RIGHT,
		SPOINT_HEAD_FACE_JAW,
		SPOINT_BODY_NECK,
		SPOINT_BODY_SPINE_SHOULDER,
		SPOINT_BODY_SPINE_MID,
		SPOINT_BODY_SPINE_BASE,
		SPOINT_BODY_SHOULDER_LEFT,
		SPOINT_BODY_SHOULDER_RIGHT,
		SPOINT_BODY_ELBOW_LEFT,
		SPOINT_BODY_ELBOW_RIGHT,
		SPOINT_BODY_WRIST_LEFT,
		SPOINT_BODY_WRIST_RIGHT,
		SPOINT_BODY_HAND_TIP_LEFT,
		SPOINT_BODY_HAND_TIP_RIGHT,

		// SPOINT version 2
		SPOINT_BODY_HIP_LEFT,
		SPOINT_BODY_HIP_RIGHT,
		SPOINT_BODY_HIP_SIDE_LEFT,
		SPOINT_BODY_HIP_SIDE_RIGHT,
		SPOINT_BODY_KNEE_LEFT,
		SPOINT_BODY_KNEE_RIGHT,
		SPOINT_BODY_ANKLE_LEFT,
		SPOINT_BODY_ANKLE_RIGHT,
		SPOINT_BODY_SHOULDER_SIDE_LEFT,
		SPOINT_BODY_SHOULDER_SIDE_RIGHT,
		SPOINT_BODY_KNEE_SIDE_LEFT,
		SPOINT_BODY_KNEE_SIDE_RIGHT,
		SPOINT_BODY_SPINE_MID_SIDE_LEFT,
		SPOINT_BODY_SPINE_MID_SIDE_RIGHT,

		// for size
		SPOINT_SIZE,
	};

	// enum: 표현(디버깅, 화면 표시)을 위한 대응 strings
	const string SPointsName[SPOINT_SIZE] =
	{
		"HEAD_TOP",
		"HEAD_HAIR",
		"HEAD_SIDE_LEFT",
		"HEAD_SIDE_RIGHT",
		"HEAD_FACE_EYE_LEFT",
		"HEAD_FACE_EYE_RIGHT",
		"HEAD_FACE_NOSE",
		"HEAD_FACE_LIP",
		"HEAD_FACE_CHEEK_LEFT",
		"HEAD_FACE_CHEEK_RIGHT",
		"HEAD_FACE_JAW",
		"BODY_NECK",
		"BODY_SPINE_SHOULDER",
		"BODY_SPINE_MID",
		"BODY_SPINE_BASE",
		"BODY_SHOULDER_LEFT",
		"BODY_SHOULDER_RIGHT",
		"BODY_ELBOW_LEFT",
		"BODY_ELBOW_RIGHT",
		"BODY_WRIST_LEFT",
		"BODY_WRIST_RIGHT",
		"SPOINT_BODY_HAND_TIP_LEFT",
		"SPOINT_BODY_HAND_TIP_RIGHT",

		"SPOINT_BODY_HIP_LEFT",
		"SPOINT_BODY_HIP_RIGHT",
		"SPOINT_BODY_HIP_SIDE_LEFT",
		"SPOINT_BODY_HIP_SIDE_RIGHT",
		"SPOINT_BODY_KNEE_LEFT",
		"SPOINT_BODY_KNEE_RIGHT",
		"SPOINT_BODY_ANKLE_LEFT",
		"SPOINT_BODY_ANKLE_RIGHT",
		"SPOINT_BODY_SHOULDER_SIDE_LEFT",
		"SPOINT_BODY_SHOULDER_SIDE_RIGHT",
		"SPOINT_BODY_KNEE_SIDE_LEFT",
		"SPOINT_BODY_KNEE_SIDE_RIGHT",
		"SPOINT_BODY_SPINE_MID_SIDE_LEFT",
		"SPOINT_BODY_SPINE_MID_SIDE_RIGHT"
	};

class SPoint
{
private:
	SPointsType type;

	CameraSpacePoint point;

public:

public:
	SPoint();
	SPoint(SPointsType type);

	~SPoint();

	string getName();
	SPointsType getType();
	CameraSpacePoint getPoint();
	void setPoint(CameraSpacePoint p);

	float Lerp(float p, float x, float y);

private:


};