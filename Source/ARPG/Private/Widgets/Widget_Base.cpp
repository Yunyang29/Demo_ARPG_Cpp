#include "Widgets/Widget_Base.h"

#include "Interfaces/PawnUIInterface.h"

void UWidget_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if(UUIComponent_Player* UIComponent_Player = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningPlayerUIComponentInitialized(UIComponent_Player);
		}
	}
}
