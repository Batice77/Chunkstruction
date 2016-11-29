#pragma once

#include "Direction.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EDirection : uint8
{
	Forward 	UMETA(DisplayName = "Forward"),
	Backward 	UMETA(DisplayName = "Backward"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right"),
	Up			UMETA(DisplayName = "Up"),
	Down		UMETA(DisplayName = "Down")
};