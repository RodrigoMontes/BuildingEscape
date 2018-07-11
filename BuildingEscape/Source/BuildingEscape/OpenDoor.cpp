// Rodrigo Montes 2018

#include "OpenDoor.h"


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
}

void UOpenDoor::OpenDoor()
{
	// Mi codigo
	AActor* Owner = GetOwner();

	// crear un rotador (rotator)
	FRotator NewRotation = FRotator(0.0f, 60.0f, 0.0f);

	// cambiar la rotacion
	Owner->SetActorRotation(NewRotation);

	UE_LOG(LogTemp, Warning, TEXT("%s is %s rotated open"), *Owner->GetName(), *Owner->GetActorRotation().ToString());
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// chequeamos el trigger volume en cada frame
	// si ActorThatOpens esta dentro del trigger volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))	//TODO Asociar ActorThatOpens a OpenDoor en Unreal Engine
	{
		OpenDoor();
	}
		
}

