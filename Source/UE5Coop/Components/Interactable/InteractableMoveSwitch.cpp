// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableMoveSwitch.h"
#include "UE5Coop/Components/MoveSwitchComponent/HowMove.h"

UInteractableMoveSwitch::UInteractableMoveSwitch()
{
	SetInteractType(EInteractType::EIT_Switch);
}

void UInteractableMoveSwitch::Interacted(ACharacter* InteractingOne)
{
	CommandMove();
}

void UInteractableMoveSwitch::CommandMove()
{
	if (MovingActor->FindComponentByClass<UHowMove>())
	{
		MovingActor->FindComponentByClass<UHowMove>()->Move();
	}
}