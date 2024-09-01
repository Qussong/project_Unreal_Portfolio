// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/GHBaseCameraShake.h"

UGHBaseCameraShake::UGHBaseCameraShake()
{
	// 지속 시간 설정 (필요에 따라)
	{
		OscillationDuration = 0.5f;			// 셰이크의 지속 시간 (초)
		OscillationBlendInTime = 0.1f;		// 시작할 때 페이드 인 시간
		OscillationBlendOutTime = 0.1f;		// 종료할 때 페이드 아웃 시간
	}

	// 회전 진동 (Pitch, Yaw, Roll)
	{
		RotOscillation.Pitch.Amplitude = FMath::RandRange(5.0f, 10.0f);
		RotOscillation.Pitch.Frequency = FMath::RandRange(20.0f, 30.0f);
		RotOscillation.Pitch.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		RotOscillation.Yaw.Amplitude = FMath::RandRange(5.0f, 10.0f);
		RotOscillation.Yaw.Frequency = FMath::RandRange(20.0f, 30.0f);
		RotOscillation.Yaw.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		RotOscillation.Roll.Amplitude = FMath::RandRange(5.0f, 10.0f);
		RotOscillation.Roll.Frequency = FMath::RandRange(20.0f, 30.0f);
		RotOscillation.Roll.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
	

	// 위치 진동 (X, Y, Z)
	{
		LocOscillation.X.Amplitude = FMath::RandRange(2.0f, 5.0f);
		LocOscillation.X.Frequency = FMath::RandRange(10.0f, 20.0f);
		LocOscillation.X.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		LocOscillation.Y.Amplitude = FMath::RandRange(2.0f, 5.0f);
		LocOscillation.Y.Frequency = FMath::RandRange(10.0f, 20.0f);
		LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;

		LocOscillation.Z.Amplitude = FMath::RandRange(2.0f, 5.0f);
		LocOscillation.Z.Frequency = FMath::RandRange(10.0f, 20.0f);
		LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}

	// FOV 진동
	{
		FOVOscillation.Amplitude = FMath::RandRange(1.0f, 2.0f);
		FOVOscillation.Frequency = FMath::RandRange(5.0f, 10.0f);
		FOVOscillation.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	}
}