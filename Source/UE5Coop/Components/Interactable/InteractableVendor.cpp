// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableVendor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"

UInteractableVendor::UInteractableVendor()
{
	SetInteractType(EInteractType::EIT_Talkable);
}

void UInteractableVendor::Interacted(ACharacter* InteractingOne)
{
	ACharacter* Character = InteractingOne;
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()); 

	// 카메라 시점 변환
	PlayerController->SetViewTargetWithBlend(GetOwner(), 1.0f, VTBlend_Linear, 1.0f, true);

	// 캐릭터 행동 제한
	if (Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->DisableMovement();
	}

	// 메뉴 위젯 생성
	if (Widget!=nullptr)
	{
		Widget->AddToViewport();
		PlayerController->bShowMouseCursor = true; // 메뉴끌때 다시 false로 돌리기 잊지말자
		PlayerController->SetIgnoreLookInput(true);
	}
}