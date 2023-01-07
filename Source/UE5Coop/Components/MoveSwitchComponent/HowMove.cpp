// Fill out your copyright notice in the Description page of Project Settings.


#include "HowMove.h"

UHowMove::UHowMove()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UHowMove::BeginPlay()
{
	Super::BeginPlay();
}


void UHowMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHowMove::Move()
{
	UE_LOG(LogTemp, Warning, TEXT("Move Function of %s is not overrided."), *GetOwner()->GetActorNameOrLabel()); //만일 자식클래스가 Move함수를 override해 사용하지 않았을 경우, 작성하지 않은 Actor의 이름과 override하지 않았음을 표시. 특히, Super를 사용하지 말 것! 
}
