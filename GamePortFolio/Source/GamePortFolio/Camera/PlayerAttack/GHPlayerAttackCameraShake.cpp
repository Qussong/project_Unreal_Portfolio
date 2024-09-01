// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/PlayerAttack/GHPlayerAttackCameraShake.h"

UGHPlayerAttackCameraShake::UGHPlayerAttackCameraShake()
{
	// 지속 시간 설정 (필요에 따라)
	{
		OscillationDuration = 0.5f;			// 셰이크의 지속 시간 (초)
		OscillationBlendInTime = 0.1f;		// 시작할 때 페이드 인 시간
		OscillationBlendOutTime = 0.1f;		// 종료할 때 페이드 아웃 시간
	}

	// 회전 진동 (Pitch, Yaw, Roll)
	{
		RotOscillation.Pitch.Amplitude = 0.3f;
		RotOscillation.Pitch.Frequency = 5.f;
		RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		RotOscillation.Yaw.Amplitude = 0.3f;
		RotOscillation.Yaw.Frequency = 5.f;
		RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		RotOscillation.Roll.Amplitude = 0.3f;
		RotOscillation.Roll.Frequency = 5.f;
		RotOscillation.Roll.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}


	// 위치 진동 (X, Y, Z)
	{
		LocOscillation.X.Amplitude = 2.f;
		LocOscillation.X.Frequency = 5.f;
		LocOscillation.X.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		LocOscillation.Y.Amplitude = 2.f;
		LocOscillation.Y.Frequency = 5.f;
		LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		LocOscillation.Z.Amplitude = 2.f;
		LocOscillation.Z.Frequency = 5.f;
		LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}

	// FOV 진동
	{
		FOVOscillation.Amplitude = 0.5f;
		FOVOscillation.Frequency = 5.f;
		FOVOscillation.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
}
