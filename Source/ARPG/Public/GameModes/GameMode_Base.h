#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Types/EnumType_Base.h"
#include "GameMode_Base.generated.h"

/**
 *
 */
UCLASS()
class ARPG_API AGameMode_Base : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameMode_Base();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "A_MY|Game Settings")
	EGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
