#pragma once

#include "CoreMinimal.h"
#include "Components/UI/UIComponent_Base.h"
#include "UIComponent_Enemy.generated.h"

class UWidget_Base;
/**
 * 
 */
UCLASS()
class ARPG_API UUIComponent_Enemy : public UUIComponent_Base
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterWidget(UWidget_Base* InWidget);

	UFUNCTION(BlueprintCallable)
	void RemoveWidgetsIfAny();

private:
	TArray<UWidget_Base*> Widgets;
};
