// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Monster/GHMonster.h"
#include "Animation/AI/Monster/GHMonsterAnim.h"

AGHMonster::AGHMonster()
{
	// Team Section
	SetTeamID(ETeamID::MONSTER);

}

void AGHMonster::SetState(EMonsterState NewState)
{
	MonsterPrevState = MonsterState;
	MonsterState = NewState;

	switch (MonsterState)
	{
	case EMonsterState::IDLE:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::IDLE);
		break;
	case EMonsterState::TRACE:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::RUN);
		break;
	case EMonsterState::ATTACK:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::ATTACK);
		break;
	case EMonsterState::DEATH:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::DEATH);
		break;
	case EMonsterState::ANGRY:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::ANGRY);
		break;
	case EMonsterState::DETECT:
		MonsterAnim->SetMonsterAnimState(EMonsterAnimState::DETECT);
		break;
	default:
		//
		break;
	}
}
