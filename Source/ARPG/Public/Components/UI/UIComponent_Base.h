#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent_Base.h"
#include "UIComponent_Base.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);

/**
 * Pawn挂载UI类
 */
UCLASS()
class ARPG_API UUIComponent_Base : public UPawnExtensionComponent_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentHealthChanged;
};
