// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_EquipWeapon.h"
#include "Character/AI/Monster/Epic/GHEpicMonster.h"

UAnimNotify_EquipWeapon::UAnimNotify_EquipWeapon()
{

}

void UAnimNotify_EquipWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AGHEpicMonster* Epic = Cast<AGHEpicMonster>(MeshComp->GetOwner());
	if (IsValid(Epic))
	{
		UChildActorComponent* WeaponActor = Epic->GetWeaponComp();
		WeaponActor->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r_weapon"));
	}

}
