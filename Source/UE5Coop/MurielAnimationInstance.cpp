// Fill out your copyright notice in the Description page of Project Settings.


#include "MurielAnimationInstance.h"
#include "GameFramework/Character.h"

void UMurielAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MurielCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UMurielAnimationInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}
