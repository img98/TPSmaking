// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableVendor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"

UInteractableVendor::UInteractableVendor()
{
	SetInteractType(EInteractType::EIT_Talkable);
}

void UInteractableVendor::Interacted(ACharacter* InteractingOne)
{
	ACharacter* Character = InteractingOne;
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()); 

	// Vendor에게 카메라 없을시 오류표시
	if (GetOwner()->FindComponentByClass<UCameraComponent>() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Interactable Vendor: %s have no Camera Component."), *GetOwner()->GetActorNameOrLabel());
		return;
	}

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
		PlayerController->bShowMouseCursor = true; //TODO: 메뉴끌때 다시 false로 돌리기 잊지말자
		PlayerController->SetIgnoreLookInput(true);
	}
}