#include "Controllers/PlayerController_Base.h"

APlayerController_Base::APlayerController_Base()
{
	PlayerTeamId = FGenericTeamId(0);
}

FGenericTeamId APlayerController_Base::GetGenericTeamId() const
{
	return PlayerTeamId;
}
