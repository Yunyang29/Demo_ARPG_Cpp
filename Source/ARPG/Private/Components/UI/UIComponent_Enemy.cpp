#include "Components/UI/UIComponent_Enemy.h"

#include "Widgets/Widget_Base.h"

void UUIComponent_Enemy::RegisterWidget(UWidget_Base* InWidget)
{
	Widgets.Add(InWidget);
}

void UUIComponent_Enemy::RemoveWidgetsIfAny()
{
	if (Widgets.IsEmpty())
	{
		return;
	}

	for (UWidget_Base* Widget : Widgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
}
