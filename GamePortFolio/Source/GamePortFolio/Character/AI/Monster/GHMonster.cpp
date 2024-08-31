// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Monster/GHMonster.h"

AGHMonster::AGHMonster()
{
	// Team Section
	SetGenericTeamId(ETeamID::MONSTER);

}

void AGHMonster::SetState(EMonsterState NewState)
{
	MonsterPrevState = MonsterState;
	MonsterState = NewState;

	switch (MonsterState)
	{
	case EMonsterState::IDLE:
		//Anim->SetAnimState(EMonsterAnimState::IDLE);
		break;
	case EMonsterState::TRACE:
		//Anim->SetAnimState(EMonsterAnimState::RUN);
		break;
	case EMonsterState::ATTACK:
		//Anim->SetAnimState(EMonsterAnimState::ATTACK);
		break;
	case EMonsterState::DEATH:
		//Anim->SetAnimState(EMonsterAnimState::DEATH);
		break;
	case EMonsterState::ANGRY:
		//Anim->SetAnimState(EMonsterAnimState::ANGRY);
		break;
	case EMonsterState::DETECT:
		//Anim->SetAnimState(EMonsterAnimState::DETECT);
		break;
	default:
		//
		break;
	}
}
