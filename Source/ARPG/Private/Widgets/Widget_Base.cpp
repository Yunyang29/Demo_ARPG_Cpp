#include "Widgets/Widget_Base.h"

#include "Interfaces/PawnUIInterface.h"

void UWidget_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if(UUIComponent_Player* UIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(UIComponent);
		}
	}
}

void UWidget_Base::InitEnemyCreatedWidget(AActor* OwningActor)
{
	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningActor))
	{
		UUIComponent_Enemy* UIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(UIComponent, TEXT("Failed to extrac a ui component from %s"), *OwningActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(UIComponent);
	}
}
