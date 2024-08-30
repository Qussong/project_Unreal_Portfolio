// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Monster/Normal/GHNormalMonster.h"
#include "Controller/AI/Monster/Normal/GHNormalMonsterController.h"

AGHNormalMonster::AGHNormalMonster()
{
	AIControllerClass = AGHNormalMonsterController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AGHNormalMonster::BeginPlay()
{

}

void AGHNormalMonster::Tick(float DeltaTime)
{

}