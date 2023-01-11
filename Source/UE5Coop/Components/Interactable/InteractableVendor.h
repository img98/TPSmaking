// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableVendor.generated.h"

/**
 * InteractableVendor 컴포넌트를 소유하게 될 캐릭터는 무조건 CameraComponent를 소지해야한다.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UE5COOP_API UInteractableVendor : public UInteractable
{
	GENERATED_BODY()
	
public:
	UInteractableVendor();

private:
	UPROPERTY(EditAnywhere)
	class UUserWidget* Widget;

protected:

public:
	virtual void Interacted(ACharacter* InteractingOne) override;

};