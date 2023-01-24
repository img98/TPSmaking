// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "HordeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UE5COOP_API AHordeEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
public:
	AHordeEnemy();

protected:
	virtual void BeginPlay() override;

	virtual void AgroSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void CombatRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void CombatRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	virtual FName GetRandomAttackSectionName() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

protected:
	FVector StartPoint;
	FName Attack1;
	FName Attack2;

public:
	virtual void GetHit(FHitResult* HitResult) override;
};
