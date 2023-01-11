// Fill out your copyright notice in the Description page of Project Settings.


#include "DrongoAnimation.h"
#include "GameFramework/Character.h"
#include "DrongoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UDrongoAnimation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ADrongoCharacter>(TryGetPawnOwner());
}

void UDrongoAnimation::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Character == nullptr)
	{
		Character = Cast<ADrongoCharacter>(TryGetPawnOwner());
	}
	if (Character == nullptr) return;

	bIsInAir = Character->GetCharacterMovement()->IsFalling();
	bIsAccelerating = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	bIsAiming = Character->GetIsAiming();
}
