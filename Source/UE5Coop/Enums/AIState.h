#pragma once

UENUM(BlueprintType)
enum class EAIState :uint8
{
	EAIS_Chasing UMETA(DisplayName = "Chasing"),
	EAIS_Holding UMETA(DisplayName = "Holding"),
	EAIS_Attacking UMETA(DisplayName = "Attacking"),

	EIT_MAX UMETA(DisplayName = "DefaultMAX")
};