// Rodrigo Montes 2018

#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Mi codigo
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting!"));

	PlayerController = GetWorld()->GetFirstPlayerController();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Funcion getter que modifica los parametros que le pasemos, en este caso un FVector y un FRotator
	PlayerController->GetPlayerViewPoint(
		OUT PlayerViewPortLocation, 
		OUT PlayerViewPortRotation);

	// calculamos el punto final del vector de prueba
	LineTraceEnd = PlayerViewPortLocation + (PlayerViewPortRotation.Vector() * Reach);

	// dibuja una linea para de muestra
	DrawDebugLine(
		GetWorld(),
		PlayerViewPortLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		1.0f
	);

	/// line trace (ray-casting) para detectar objetos
	FHitResult LineTraceHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		PlayerViewPortLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// mostrar lo que colisionamos con el codigo anterior
	AActor* ActorHit = LineTraceHit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("actor: %s"), *(ActorHit->GetName()));
	}
	
}

