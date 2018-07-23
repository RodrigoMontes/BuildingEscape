// Rodrigo Montes 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h" 

// Always the last include!!
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector PlayerViewPortLocation;
	FRotator PlayerViewPortRotation;
	float Reach = 100.0f;	// how far we can grab objects

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Get the start point for the trace line (with reach)
	FVector GetReachLineStart();
	// Get the end point for the trace line (with reach)
	FVector GetReachLineEnd();

	// Line traces and grabs what's in reach
	void Grab();
	// Called on key release
	void Release();

	// Finds a physics handle component
	void FindPhysicsHandleComponent();
	// Finds and binds the input component for grabbing
	void SetupInputComponent();
	// Returns the first physics body in reach and returns it
	const FHitResult GetFirstPhysicsBodyInReach();
	
};