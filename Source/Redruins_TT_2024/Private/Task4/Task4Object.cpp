// RedRuins Softworks (c)


#include "Task4Object.h"

bool UTask4Object::IsSupportedForNetworking() const
{
	return true;
}

void UTask4Object::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	if (const UBlueprintGeneratedClass* BlueprintGeneratedClass = Cast<UBlueprintGeneratedClass>(GetClass()))
	{
		BlueprintGeneratedClass->GetLifetimeBlueprintReplicationList(OutLifetimeProps);
	}
}
