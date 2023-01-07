// Fill out your copyright notice in the Description page of Project Settings.


#include "HowMoveBarrel.h"

UHowMoveBarrel::UHowMoveBarrel()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHowMoveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalLocation = GetOwner()->GetActorLocation();
}


void UHowMoveBarrel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsMoving)
	{
		FVector TargetLocation = OriginalLocation + MoveOffset;
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		float Speed = MoveOffset.Length() / MoveTime;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}

}

void UHowMoveBarrel::Move()
{
	if (bIsMoving == false)
	{
		bIsMoving = true;
	}
	else
	{
		bIsMoving = false;
	}
}
