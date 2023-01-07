// Fill out your copyright notice in the Description page of Project Settings.


#include "DrongoAnimation.h"
#include "GameFramework/Character.h"
#include "DrongoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDrongoAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	DrongoCharacter = Cast<ADrongoCharacter>(TryGetPawnOwner());
}

void UDrongoAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (DrongoCharacter == nullptr)
	{
		DrongoCharacter = Cast<ADrongoCharacter>(TryGetPawnOwner());
	}
	if (DrongoCharacter == nullptr) return;

	bIsInAir = DrongoCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = DrongoCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	bIsAiming = DrongoCharacter->GetIsAiming();
}
