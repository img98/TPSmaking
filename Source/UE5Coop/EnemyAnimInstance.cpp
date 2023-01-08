// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Enemy = Cast<AEnemyCharacter>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Enemy == nullptr)
	{
		Enemy = Cast<AEnemyCharacter>(TryGetPawnOwner());
	}
	if (Enemy == nullptr) return;

	bIsInAir = Enemy->GetCharacterMovement()->IsFalling();
	bIsAccelerating = Enemy->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;
	FVector Velocity = Enemy->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();
}