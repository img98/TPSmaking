// Fill out your copyright notice in the Description page of Project Settings.


#include "HordeEnemy.h"
#include "EnemyCharacter.h"
#include "UE5Coop/AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "UE5Coop/Character/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

AHordeEnemy::AHordeEnemy() :
	Attack1(TEXT("AttackSwing")),
	Attack2(TEXT("AttackSlam"))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHordeEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AEnemyAIController>(GetController());
	if (EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool(FName("CanAttack"), true);
	}

	StartPoint = GetActorLocation();
	/** DrawDebugSphere(
		GetWorld(),
		StartPoint,
		25.f,
		12,
		FColor::Red,
		true
	);
	*/

	if (EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("StartPoint"), StartPoint);
	}
}

// Called every frame
void AHordeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHordeEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHordeEnemy::AgroSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AHordeEnemy::CombatRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	auto Character = Cast<AShooterCharacter>(OtherActor);
	if (Character == nullptr) return;

	bInAttackRange = true;
	EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), bInAttackRange);
}
void AHordeEnemy::CombatRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr) return;
	auto Character = Cast<AShooterCharacter>(OtherActor);
	if (Character == nullptr) return;

	bInAttackRange = false;
	EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), bInAttackRange);
}

void AHordeEnemy::GetHit(FHitResult* HitResult)
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

FName AHordeEnemy::GetRandomAttackSectionName()
{
	FName SectionName;
	const int32 Section{ FMath::RandRange(1,2) };
	switch (Section)
	{
	case 1:
		SectionName = Attack1;
		break;
	case 2:
		SectionName = Attack2;
		break;
	}

	return SectionName;
}