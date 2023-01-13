// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "UE5Coop/AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "UE5Coop/Character/ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetMesh());
	CombatRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CombatRangeSphere"));
	CombatRangeSphere->SetupAttachment(GetMesh());

	bStunned = false;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::AgroSphereOverlap);
	CombatRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::CombatRangeOverlap);
	CombatRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::CombatRangeEndOverlap);

	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

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

void AEnemyCharacter::CombatRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;
	auto Character = Cast<AShooterCharacter>(OtherActor);
	if (Character == nullptr) return;

	bInAttackRange = true;
	EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), bInAttackRange);
}
void AEnemyCharacter::CombatRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == nullptr) return;
	auto Character = Cast<AShooterCharacter>(OtherActor);
	if (Character == nullptr) return;

	bInAttackRange = false;
	EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), bInAttackRange);
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
		EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("Stunned"), Stunned);
	}
	
}

void AEnemyCharacter::PlayAttackMontage(FName Section, float PlayRate)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

FName AEnemyCharacter::GetRandomAttackSectionName()
{
	FName SectionName;
	const int32 Section{ FMath::RandRange(1,2) };
	switch(Section)
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