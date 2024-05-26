// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Task4Object.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class REDRUINS_TT_2024_API UTask4Object : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
