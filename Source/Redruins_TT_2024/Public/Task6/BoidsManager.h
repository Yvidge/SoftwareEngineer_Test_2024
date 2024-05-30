// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BoidsManager.generated.h"

// TODO Optimization via batching

/**
 * 
 */
UCLASS()
class REDRUINS_TT_2024_API UBoidsManager : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
};
