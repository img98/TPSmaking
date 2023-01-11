// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "UE5Coop/AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "UE5Coop/Character/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetMesh());

	bStunned = false;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::AgroSphereOverlap);

	/** Get AI Controller */
	EnemyController = Cast<AEnemyAIController>(GetController());

	StartPoint = GetActorLocation();
	DrawDebugSphere(
		GetWorld(),
		StartPoint,
		25.f,
		12,
		FColor::Red,
		true
	);

	if (EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("StartPoint"), StartPoint);

		EnemyController->RunBehaviorTree(BehaviorTree);
	}
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::AgroSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	auto Character = Cast<AShooterCharacter>(OtherActor);
	{
		if (Character)
		{
			EnemyController->GetBlackboardComponent()->SetValueAsObject(TEXT("AgroTarget"), Character);
		}
	}
}

void AEnemyCharacter::GetHit(FHitResult* HitResult)
{
	const float Stunned = FMath::FRandRange(0.f, 1.f);
	if (Stunned < StunChance)
	{
		//Stun the Enemy
		
		//PlayHitMontage(FName("HitReact"));
		SetStunned(true);
		//TODO: ABP에서 해당 애니메이션 출력끝나면 bStunned를 false로 되돌리자.
	}
}

void AEnemyCharacter::SetStunned(bool Stunned)
{
	bStunned = Stunned;

	if (EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool(
			TEXT("Stunned"),
			Stunned);
	}
	
}