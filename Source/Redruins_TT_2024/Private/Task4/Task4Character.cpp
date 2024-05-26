// RedRuins Softworks (c)


#include "Redruins_TT_2024/Public/Task4/Task4Character.h"

#include "Task4Object.h"
#include "Net/UnrealNetwork.h"


ATask4Character::ATask4Character()
{
	bReplicates = true;
	bReplicateUsingRegisteredSubObjectList = true;
}

UObject* ATask4Character::CreateSubobject(TSubclassOf<UTask4Object> Class)
{
	CleanupSubobject();

	if (Class->IsValidLowLevel())
	{
		ReplicatedSubobject = NewObject<UTask4Object>(this, Class);
		AddReplicatedSubObject(ReplicatedSubobject);
		return ReplicatedSubobject;
	}

	return nullptr;
}

void ATask4Character::CleanupSubobject()
{
	if (ReplicatedSubobject)
	{
		RemoveReplicatedSubObject(ReplicatedSubobject);
	}
}

void ATask4Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATask4Character, ReplicatedSubobject);
}

