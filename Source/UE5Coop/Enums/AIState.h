#pragma once

UENUM(BlueprintType)
enum class EAIState :uint8
{
	EAIS_Holding UMETA(DisplayName = "Holding"),
	EAIS_Attacking UMETA(DisplayName = "Attacking"),
	EAIS_Recovery UMETA(DisplayName = "Recovery"),

	EIT_MAX UMETA(DisplayName = "DefaultMAX")
};