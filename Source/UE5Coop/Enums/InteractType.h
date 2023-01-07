#pragma once

UENUM(BlueprintType)
enum class EInteractType :uint8
{
	EIT_Talkable UMETA(DisplayName = "Talkable"),
	EIT_Usable UMETA(DisplayName = "Usable"),
	EIT_Switch UMETA(DisplayName = "Switch"),

	EIT_MAX UMETA(DisplayName = "DefaultMAX")
};