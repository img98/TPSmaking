// Fill out your copyright notice in the Description page of Project Settings.


#include "DrongoCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "DrongoAnimation.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "UE5Coop/Components/Interactable/Interactable.h"
#include "CollisionQueryParams.h"

ADrongoCharacter::ADrongoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MainSpringArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("Main SpringArm"));
	MainSpringArm->SetupAttachment(GetMesh());
	MainSpringArm->TargetArmLength = ArmLength;
	//MainSpringArm->bUsePawnControlRotation = true;

	MainCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(MainSpringArm, USpringArmComponent::SocketName);
	//MainCamera->bUsePawnControlRotation = false;
}

void ADrongoCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void ADrongoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimButtonPressNRelease();
}

void ADrongoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ADrongoCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ADrongoCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ADrongoCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ADrongoCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &ADrongoCharacter::AimPressed);
	PlayerInputComponent->BindAction(TEXT("Aim"), IE_Released, this, &ADrongoCharacter::AimReleased);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrongoCharacter::FireButtonPressed);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ADrongoCharacter::FireButtonReleased);
	PlayerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &ADrongoCharacter::Interact);
}

void ADrongoCharacter::AimPressed()
{	
	bIsAiming = true;
}
void ADrongoCharacter::AimReleased()
{
	bIsAiming = false;
}
void ADrongoCharacter::AimButtonPressNRelease()
{
	if (bIsAiming)
	{
		float CurrentLength = MainSpringArm->TargetArmLength;
		MainSpringArm->TargetArmLength = FMath::FInterpTo(CurrentLength, AimLength, GetWorld()->GetDeltaSeconds(), 15.f);
	}
	else if (!bIsAiming)
	{
		float CurrentLength = MainSpringArm->TargetArmLength;
		MainSpringArm->TargetArmLength = FMath::FInterpTo(CurrentLength, ArmLength, GetWorld()->GetDeltaSeconds(), 15.f);
	}

}
void ADrongoCharacter::FireButtonPressed()
{

}
void ADrongoCharacter::FireButtonReleased()
{

}

void ADrongoCharacter::Interact()
{
	FHitResult HitResult;
	float SweepRadius = 10.f; //나중에 Interact컴포넌트로 만들어서 헤더에 저장하는게 좋을듯
	FCollisionShape Sphere = FCollisionShape::MakeSphere(SweepRadius); //sweep용 구체 만들기
	float InteractDistance = 200.f; //이것도 헤더에 넣자
	FCollisionQueryParams ParamExceptSelf(FName("InteractSweepTrace"), false, this); //자신에게 collision되지않게 제외하는 충돌param

	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult, GetActorLocation(), GetActorLocation()+GetActorForwardVector()* InteractDistance,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere,
		ParamExceptSelf
	);

	if (HasHit)
	{
		if (HitResult.GetActor()->FindComponentByClass<UInteractable>())
		{
			HitResult.GetActor()->FindComponentByClass<UInteractable>()->Interacted(this); //HitResult의 액터가 갖고있는 Interactable컴포의 Interacted를 실행
		}
		
	}

}

void ADrongoCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ADrongoCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ADrongoCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ADrongoCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
