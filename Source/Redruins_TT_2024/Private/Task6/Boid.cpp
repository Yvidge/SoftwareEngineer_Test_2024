// RedRuins Softworks (c)


#include "Task6/Boid.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void ABoid::BeginPlay()
{
	Super::BeginPlay();

	Velocity = GetActorForwardVector() * BaseSpeed;
	//Target = UGameplayStatics::GetActorOfClass(this, );
}

void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleBoidMovement(DeltaTime);
}

FVector ABoid::HandleLocationWrapping(FVector& ResultLocation)
{
	if(ResultLocation.X > BorderDistance || ResultLocation.X < -BorderDistance)
	{
		ResultLocation.X *= -1;
	}

	if(ResultLocation.Y > BorderDistance || ResultLocation.Y < -BorderDistance)
	{
		ResultLocation.Y *= -1;
	}

	if(ResultLocation.Z > BorderDistance || ResultLocation.Z < -BorderDistance)
	{
		ResultLocation.Z *= -1;
	}

	return ResultLocation;
}

void ABoid::HandleBoidMovement(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector Acceleration = FVector::Zero();
	//Acceleration = FVector(BaseSpeed, 0,0);
	//Acceleration = GetActorForwardVector() * BaseSpeed;

	auto NearbyBoids = GetNearbyBoids();
	NearbyBoids.FilterByPredicate([this](const ABoid* Boid)
	{
		return IsInVision(Boid);
	});


	// Target force
	if(Target)
	{
		FVector OffsetToTarget = Target->GetActorLocation() - CurrentLocation;
		Acceleration += SteerToward(OffsetToTarget) * TargetForceWeight;
	}
	
	// Simple avoidance TODO Traces
	FVector AvoidanceDirection = FVector::Zero();
	for (ABoid* NearbyBoid : NearbyBoids)
	{
		FVector OtherLocation = NearbyBoid->GetActorLocation();
		float Ratio = FMath::Clamp(1 - FVector::DistSquared(OtherLocation, CurrentLocation) / (SeparationRadius * SeparationRadius), 0.f, 1.f);
		AvoidanceDirection -= (OtherLocation - CurrentLocation) * Ratio;
		AvoidanceDirection.Normalize();
		DrawDebugLine(GetWorld(), CurrentLocation, OtherLocation, FColor::Cyan, false, -1, 0, Ratio * 50);
	}

	

	if(NearbyBoids.Num() > 0)
	{
		// Prepare data
		FVector AverageHeading = FVector::Zero();
		FVector OffsetToNearbyBoidsCenter = FVector::Zero();
		FVector NearbyBoidsCenter = FVector::Zero();
		for (ABoid* NearbyBoid : NearbyBoids)
		{
			AverageHeading += NearbyBoid->GetActorForwardVector();
			NearbyBoidsCenter += NearbyBoid->GetActorLocation();
		}
		AverageHeading /= NearbyBoids.Num();
		NearbyBoidsCenter /= NearbyBoids.Num();
		OffsetToNearbyBoidsCenter = NearbyBoidsCenter - CurrentLocation;

		
		FVector AlignmentForce = FVector::Zero();
		FVector CohesionForce = FVector::Zero();

		AlignmentForce = SteerToward(AverageHeading) * AlignmentForceWeight;
		DrawDebugLine(GetWorld(), GetActorLocation(), CurrentLocation + AlignmentForce, FColor::Orange);

		CohesionForce = SteerToward(OffsetToNearbyBoidsCenter) * CohesionForceWeight;
		DrawDebugLine(GetWorld(), GetActorLocation(), NearbyBoidsCenter, FColor::Purple);

		Acceleration += AlignmentForce;
		Acceleration += CohesionForce;
	}
	
	
	Acceleration += AvoidanceDirection * SeparationForceWeight;

	Velocity += Acceleration * DeltaTime;
	float Speed = Velocity.Length();
	FVector Direction = Velocity / Speed;
	Speed = FMath::Clamp(Speed, MinSpeed, MaxSpeed);
	Velocity = Direction * Speed;
	
	FVector ResultLocation = CurrentLocation + Velocity * DeltaTime;

	SetActorRotation(UKismetMathLibrary::MakeRotFromX(Direction));
	SetActorLocation(HandleLocationWrapping(ResultLocation));
}

bool ABoid::IsInVision(const ABoid* OtherBoid) const
{
	return GetActorForwardVector().Dot(GetActorLocation() - OtherBoid->GetActorLocation()) < VisionConeThreshold;
}

TArray<ABoid*> ABoid::GetNearbyBoids() const
{
	TArray<ABoid*> Result;

	return GetNearbyBoidsViaCollision();
}

TArray<ABoid*> ABoid::GetNearbyBoidsViaCollision() const
{
	TArray<ABoid*> Result;
	TArray<AActor*> ActorResults;
	GetOverlappingActors(ActorResults, StaticClass());

	for (AActor* ActorResult : ActorResults)
	{
		Result.Add(Cast<ThisClass>(ActorResult));
	}

	return Result;
}

FVector ABoid::SteerToward(FVector Vector) const
{
	Vector.Normalize();
	FVector Result = (Vector * MaxSpeed) - Velocity;
	return Result.GetClampedToMaxSize(MaxSteerForce);
}

