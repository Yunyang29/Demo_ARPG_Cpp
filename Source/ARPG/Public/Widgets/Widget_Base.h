#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Base.generated.h"

class UUIComponent_Player;
/**
 * 
 */
UCLASS()
class ARPG_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Owning Player UI Component Initialized"))
	void BP_OnOwningPlayerUIComponentInitialized(UUIComponent_Player* OwningUiComponent);
};
