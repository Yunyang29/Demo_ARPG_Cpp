#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UUIComponent_Player;
class UUIComponent_Base;
class UUIComponent_Enemy;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARPG_API IPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UUIComponent_Base*   GetUIComponent() const = 0;
	virtual UUIComponent_Player* GetPlayerUIComponent() const;
	virtual UUIComponent_Enemy*  GetEnemyUIComponent() const;
};
