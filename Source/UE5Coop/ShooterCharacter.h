// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class UE5COOP_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void AimTest();
private:

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* CharacterMesh;
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* AimSpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* AimCamera;


public:	



};
