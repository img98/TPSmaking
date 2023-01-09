// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "UE5Coop/AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "DrongoCharacter.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetMesh());
	AttackRadius = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRadius"));
	AttackRadius->SetupAttachment(GetMesh());
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

	auto Character = Cast<ADrongoCharacter>(OtherActor);
	{
		if (Character)
		{
			EnemyController->GetBlackboardComponent()->SetValueAsObject(TEXT("AgroTarget"), Character);
		}
	}
}


void AEnemyCharacter::AttackRadiusOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr) return;

	auto Character = Cast<ADrongoCharacter>(OtherActor);
	{
		/** TODO: 캐릭터 Enum State를 설정해 공격애니메이션 출력하고 공격함수 실행 할것 */
	}
}


