// Rodrigo Montes 2018

#include "OpenDoor.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// busca top down el pawn (player), desde el mundo, al controlador, al player
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();

	if (!PressurePlate) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate missing for %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// we check on each tick if volume on trigger volume is higher or equal to the max mass threshold
	if (GetTotalMassOfActorsOnPlate() >= PlateMaxMass) 
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray <AActor*>  OverlappingActors;

	// Find the actors overlapping the pressure plate
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	/// Iterate through them adding their masses
	for (const auto* ActorThatOverlaps : OverlappingActors)
	{
		TotalMass += ActorThatOverlaps->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}
