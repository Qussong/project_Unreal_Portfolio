// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GHBaseWidgetComponent.h"

UGHBaseWidgetComponent::UGHBaseWidgetComponent()
{
}

void UGHBaseWidgetComponent::OnRegister()
{
	// 컴포넌트가 월드에 추가되거나 소유된 액터가 월드에 배치될 떄 호출
	// UWidgetComponent 가 처음 활성화될 때, 초기화 작업 수행
	Super::OnRegister();
}

void UGHBaseWidgetComponent::InitWidget()
{
	// WidgetClass에 기반하여 위젯을 생성하는 초기화 작업
	Super::InitWidget();
}

void UGHBaseWidgetComponent::BeginPlay()
{
	// 컴포넌트를 소유한 액터가 플레이를 시작할 때 호출
	// 게임 시작 시 초기화 작업을 할 때 사용
	Super::BeginPlay();
}

void UGHBaseWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// 컴포넌트가 매 프레임 호출되어 업데이트할 수 있도록한다.
	// 위젯의 상태를 업데이트하거나 애니메이션을 처리할 때 사용
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
