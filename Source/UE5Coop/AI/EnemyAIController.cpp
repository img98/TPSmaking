// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UE5Coop/Character/EnemyCharacter.h"
#include "Navigation/CrowdFollowingComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer) : //Detour AI를 위해 생성자에 ObjectInitializer 넘겨준것
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))) //Cpp상 Detour Crowd Ai Controller가 존재하지 않기에, 수동으로 Nav컴포넌트 추가
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(BlackboardComponent);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (InPawn == nullptr) return;

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn);
	if (Enemy)
	{
		if (Enemy->GetBehaviorTree())
		{
			BlackboardComponent->InitializeBlackboard(*(Enemy->GetBehaviorTree()->BlackboardAsset));
		}
	}
}