// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DrongoCharacter.generated.h"

UCLASS()
class UE5COOP_API ADrongoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADrongoCharacter();

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void AimPressed();
	void AimReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	void Interact();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MainSpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MainCamera;
	float ArmLength = 200.f;
	float AimLength = 40.f;
	

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool GetIsAiming() { return bIsAiming; };
	UFUNCTION(BlueprintCallable)
	void SetIsAiming(bool bBool) { bIsAiming = bBool; };
	UFUNCTION(BlueprintCallable)
	void AimButtonPressNRelease();
	bool bIsAiming = false;
};
