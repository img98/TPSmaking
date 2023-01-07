// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE5Coop/Enums/InteractType.h"

#include "Interactable.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE5COOP_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractable();

private:
	UPROPERTY(VisibleAnywhere)
	EInteractType InteractType; //사용할 Interactable 자식의 이름을 Enum에 추가해 사용하자

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetInteractType(EInteractType SetType);
	FORCEINLINE EInteractType GetInteractType() const { return InteractType; } //사용될 Interactable자식의 이름을 알아야할때 사용
	
	virtual void Interacted(ACharacter* InteractingOne); //사용자가 이 함수만을 호출하면된다. 세부내용은 자식클래스에서 작성하기
};