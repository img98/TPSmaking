// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "UE5Coop/Enums/InteractType.h"

UInteractable::UInteractable()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractType = EInteractType::EIT_MAX;
}


void UInteractable::BeginPlay()
{
	Super::BeginPlay();

	
}


void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractable::SetInteractType(EInteractType SetType)
{
	InteractType = SetType;
}

void UInteractable::Interacted(ACharacter* InteractingOne)
{
	UE_LOG(LogTemp, Warning, TEXT("Interacted Function of %s is not overrided."), *GetOwner()->GetActorNameOrLabel()); //만일 자식클래스가 Interacted함수를 override해 사용하지 않았을 경우, 상호작용을 시도한 Actor의 이름과 override하지 않았음을 표시. 특히, Super를 사용하지 말 것! 
}
