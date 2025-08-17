#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Base.generated.h"

class UUIComponent_Enemy;
class UUIComponent_Player;
/**
 * 
 */
UCLASS()
class ARPG_API UWidget_Base : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Owning Player UI Component Initialized"))
	void BP_OnOwningPlayerUIComponentInitialized(UUIComponent_Player* OwningUiComponent);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UUIComponent_Enemy* OwningUiComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningActor);
};
