#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Base.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API APlayerController_Base : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APlayerController_Base();
	virtual FGenericTeamId GetGenericTeamId() const override; // IGenericTeamAgentInterface Interface
private:
	FGenericTeamId PlayerTeamId;
};
