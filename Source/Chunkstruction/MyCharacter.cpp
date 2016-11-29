// Fill out your copyright notice in the Description page of Project Settings.

#include "Chunkstruction.h"
#include "MyCharacter.h"
#include "Frame.h"
#include "ChunkComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Emerald, FString::Printf(TEXT("Current BlockType: %d"), blockType));

	FHitResult TraceHitResult;
	TraceAim(TraceHitResult);

	if (TraceHitResult.bBlockingHit) {
		if (TraceHitResult.GetActor()) {
			AFrame* frame = Cast<AFrame>(TraceHitResult.GetActor());
			if (frame)
			{
				FVector pos1 = frame->GetActorTransform().InverseTransformPosition(TraceHitResult.Location + (-TraceHitResult.Normal /** 25*/)).GridSnap(50);
				DrawDebugBox(GetWorld(), frame->GetActorTransform().TransformPosition(pos1), FVector(25.5), frame->GetActorQuat(), FColor(255, 0, 0, 100));

				pos1 = frame->GetActorTransform().InverseTransformPosition(TraceHitResult.Location -TraceHitResult.Normal + TraceHitResult.Normal * 50).GridSnap(50);
				DrawDebugBox(GetWorld(), frame->GetActorTransform().TransformPosition(pos1), FVector(25.5), frame->GetActorQuat(), FColor(0, 255, 0, 100));
			}
			else
				DrawDebugBox(GetWorld(), TraceHitResult.Location + (TraceHitResult.Normal * 25), FVector(25), UKismetMathLibrary::MakeRotFromZ(TraceHitResult.Normal).Quaternion(), FColor(0, 170, 200, 100));
		}
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComp)
{
	Super::SetupPlayerInputComponent(InputComp);

	InputComp->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	InputComp->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	InputComp->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	InputComp->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	InputComp->BindAction("RemoveBlock", EInputEvent::IE_Pressed, this, &AMyCharacter::OnRemoveBlock);
	InputComp->BindAction("PlaceBlock", EInputEvent::IE_Pressed, this, &AMyCharacter::OnPlaceBlock);

	InputComp->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	InputComp->BindAction("NextBlock", EInputEvent::IE_Pressed, this, &AMyCharacter::SelectNextBlock);
}

void AMyCharacter::OnRemoveBlock()
{
	FHitResult TraceHitResult;
	TraceAim(TraceHitResult);

	if (TraceHitResult.bBlockingHit) {
		AFrame* frame = Cast<AFrame>(TraceHitResult.GetActor());
		if (frame)
		{
			FVector pos = frame->GetActorTransform().InverseTransformPosition(TraceHitResult.Location -TraceHitResult.Normal).GridSnap(50);
			pos /= UChunkComponent::blockSize;
			frame->SetBlock(pos.X, pos.Y, pos.Z, FBlock(0));
		}
	}
}

void AMyCharacter::OnPlaceBlock()
{
	FHitResult TraceHitResult;
	TraceAim(TraceHitResult);

	if (TraceHitResult.bBlockingHit)
	{
		AFrame* frame = Cast<AFrame>(TraceHitResult.GetActor());
		if (frame)
		{
			FVector pos = frame->GetActorTransform().InverseTransformPosition(TraceHitResult.Location -TraceHitResult.Normal + (TraceHitResult.Normal * 50)).GridSnap(50);
			pos /= UChunkComponent::blockSize;
			frame->SetBlock(pos.X, pos.Y, pos.Z, FBlock(blockType));
		}
		else {
			FActorSpawnParameters SpawnParams;
			frame = GetWorld()->SpawnActor<AFrame>(AFrame::StaticClass(), TraceHitResult.Location + (TraceHitResult.Normal * 25), UKismetMathLibrary::MakeRotFromZ(TraceHitResult.Normal), SpawnParams);
			frame->SetBlock(0, 0, 0, FBlock(blockType));
		}
	}
	
}

void AMyCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyCharacter::TraceAim(FHitResult &hitResult)
{
	FVector Start;
	FRotator RotEyes;
	GetActorEyesViewPoint(Start, RotEyes);

	const FVector End = Start + RotEyes.Vector() * 600;

	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("VisualBlock_Trace")), false, this);

	GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, TraceParams);
}

void AMyCharacter::SelectNextBlock()
{
	if (blockType >= 2) blockType = 0;
	blockType++;
}