// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class REDRUINS_TT_2024_API ABoid : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	FVector HandleLocationWrapping(FVector& ResultLocation);

	void HandleBoidMovement(float DeltaTime);

	bool IsInVision(const ABoid* OtherBoid) const;

	UFUNCTION()
	TArray<ABoid*> GetNearbyBoids() const;

	TArray<ABoid*> GetNearbyBoidsViaCollision() const;

	FVector SteerToward(FVector Vector) const;
	
protected:

	UPROPERTY(VisibleInstanceOnly)
	FVector Velocity;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TObjectPtr<AActor> Target; 

	// TODO Move to some config
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float BorderDistance = 5000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float BaseSpeed = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float MinSpeed = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float MaxSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float MaxSteerForce = 600.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float SeparationRadius = 300.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float SeparationForceWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float AlignmentForceWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float CohesionForceWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float TargetForceWeight = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	float VisionConeThreshold = 0.5f;
};
