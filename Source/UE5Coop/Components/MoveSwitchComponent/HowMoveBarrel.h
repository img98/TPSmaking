// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HowMove.h"
#include "HowMoveBarrel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5COOP_API UHowMoveBarrel : public UHowMove
{
	GENERATED_BODY()

public:	
	UHowMoveBarrel();

private:
	bool bIsMoving = false;
	FVector OriginalLocation;
	UPROPERTY(EditInstanceOnly)
	FVector MoveOffset;
	UPROPERTY(EditInstanceOnly)
	float MoveTime = 4;
		
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Move() override;
		
};