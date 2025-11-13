#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/EnumType_Base.h"
#include "SaveGame_Base.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API USaveGame_Base : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EGameDifficulty SavedCurrentGameDifficulty;
};
