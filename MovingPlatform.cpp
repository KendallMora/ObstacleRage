#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void MyTestFunction(float MyFloatParam, FString MyStringParam)
{
	
	float MyFloat = MyFloatParam - 3.0f;
	UE_LOG(LogTemp, Display, TEXT("bla bla bla %f  my name is %s!"),MyFloatParam, *MyStringParam);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	FString MyName = GetName();
    MyTestFunction(5.0f, MyName);
	
}


// Called every frame in a loop
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	DistanceMoved = GetDistanceMoved();

	if (DistanceMoved >= MoveDistance)
	{
		float Overshoot = DistanceMoved - MoveDistance;

		UE_LOG(LogTemp, Display, TEXT("The overshoot is about %f"), Overshoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();

		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;

		SetActorLocation(NewStartLocation);

		StartLocation = NewStartLocation;

		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
     FVector CurrentLocation = GetActorLocation();
	             
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);

	SetActorLocation(CurrentLocation);
	}
}
void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//it will rotate the platform
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}



float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation, GetActorLocation());
}
