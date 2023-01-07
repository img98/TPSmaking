// Fill out your copyright notice in the Description page of Project Settings.


#include "VendorNPC.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UE5Coop/Components/Interactable/InteractableVendor.h"

AVendorNPC::AVendorNPC()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleCollider;	

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(CapsuleCollider);
	
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(SkeletalMesh);

	InteractableComponent = CreateDefaultSubobject<UInteractableVendor>(TEXT("InteractableVendor"));
}

void AVendorNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVendorNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

