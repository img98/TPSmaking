// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableMoveSwitch.generated.h"

/**
 * 스위치를 눌렀을때 종류에 따라 여러 움직임을 행해야 하듯이, 2차적으로 다양한 동작을 수행해야 하는 경우에 사용
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5COOP_API UInteractableMoveSwitch : public UInteractable
{
	GENERATED_BODY()

public:
	UInteractableMoveSwitch();

private:
	UPROPERTY(EditInstanceOnly)
	class AActor* MovingActor; //움직여야할 대상(Actor)선택 (UE에디터에서 직접 Pick하기를 권장)
	//움직일 대상이 여럿일 경우 MainActor를 하나 지정하여, 해당 Actor의 HowMove의 자식에서 다른 Actor의 움직임을 호출하길 권장

protected:

public:
	virtual void Interacted(ACharacter* InteractingOne) override;
	void CommandMove(); //대상Actor에게 움직이라고 명령, 대상은 HowMove계열 컴포넌트를 반드시 소지해야함
};