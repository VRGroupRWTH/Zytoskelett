#include "CellMesh.h"

#include "Cell.h"
#include "CellDataFactory.h"

#include <stdexcept>


/*
 * describes the actor, that is visible in the scene
 */

float ACellMeshActorComponent::DensityRange = 0.0f;
float ACellMeshActorComponent::DensityMin = 0.0f;
float ACellMeshActorComponent::DensityScale = 10.0f;
float ACellMeshActorComponent::DensityShift = .5f;

ACellMeshActorComponent::ACellMeshActorComponent()
	:Super() {

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	Cell = UCellDataFactory::GetCell();
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset1(TEXT("/Game/Maps/Filamente/01_-_Default"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset2(TEXT("/Game/Maps/Filamente/02_-_Default"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset3(TEXT("/Game/Maps/Filamente/03_-_Default"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset4(TEXT("/Game/Maps/Filamente/04_-_Default"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset5(TEXT("/Game/Maps/Filamente/05_-_Default"));
	if (!( MaterialAsset1.Succeeded()
		&& MaterialAsset2.Succeeded()
		&& MaterialAsset3.Succeeded()
		&& MaterialAsset4.Succeeded()
		&& MaterialAsset5.Succeeded())) {
		throw std::runtime_error("The object you are looking for could not be found");
	}
	TArray<UMaterial*> classes({ MaterialAsset1.Object, MaterialAsset2.Object, MaterialAsset3.Object, MaterialAsset4.Object, MaterialAsset5.Object });

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("SphereComp"));
	SetRootComponent(Sphere);
	
	RootComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	Sphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	
	const float RadiusScale = 10.0f / 1.0f;
	
	if (Cell != nullptr) 
	{
		
		const FVector Origin = Cell->GetBoundingBox().GetCenter();
		for (UFilament* Filament : Cell->GetFilaments()) 
		{
			
			TArray<UCellData*> CellData = Filament->GetVertices();
			const float Radius = CellData[0]->Density;
			TArray<FVector> Vertices;
			TArray<int32> Triangles;
			TArray<FVector> Normals;
			TArray<FVector2D> UV0;
			TArray<FLinearColor> VertexColors;
			TArray<FProcMeshTangent> Tangents;
			for (int i = 0; i < CellData.Num() - 1; ++i)
			{
				const float PositionScale = 1000.f;
				
				UCellData* CellDataStart = CellData[i];
				UCellData* CellDataEnd = CellData[i + 1];

				FVector Start = FVector(CellDataStart->X, CellDataStart->Y, CellDataStart->Z) - Origin;
				Start *= PositionScale;
				FVector End = FVector(CellDataEnd->X, CellDataEnd->Y, CellDataEnd->Z) - Origin;
				End *= PositionScale;
				
				CreateCylinder(Vertices, Triangles, Start, End, ( ( ( (Radius - DensityMin) / DensityRange) * DensityScale) + DensityShift) * RadiusScale);	
			}
			FString FilamentID = "Filament_";
			FilamentID.AppendInt(CellData[0]->LineNumber);
			UProceduralMeshComponent* CylinderMesh = CreateDefaultSubobject<UProceduralMeshComponent>(FName(*FilamentID));
			CylinderMesh->CreateMeshSection_LinearColor(
				0,
				Vertices,
				Triangles,
				TArray<FVector>(),
				TArray<FVector2D>(),
				TArray<FLinearColor>(),
				TArray<FProcMeshTangent>(),
				true);
			UMaterial* Material = classes[CellData[0]->Class - 1];
			CylinderMesh->SetMaterial(0, Material);
			CylinderMesh->SetupAttachment(RootComponent);

			ComponentCellMap.Emplace(CylinderMesh, Filament);
			
			
		}
	}
}

UCell * ACellMeshActorComponent::GetCell()
{
	return Cell;
}

void ACellMeshActorComponent::Tick(float DeltaSeconds)
{
	
	//SetActorRotation(CurrentRotation);
}

void ACellMeshActorComponent::CreateCylinder(
	TArray<FVector>& Vertices,
	TArray<int32>& Triangles,
	FVector Start,
	FVector End,
	float Radius,
	int Resolution) 
{
	int VertexOffset = Vertices.Num();
	Vertices.SetNum((Resolution + 1) * 2 + VertexOffset);
	int TriangleOffset = Triangles.Num();
	Triangles.SetNum(Resolution * 4 * 3 + TriangleOffset);

	Vertices[VertexOffset] = Start;
	Vertices[VertexOffset + Resolution + 1] = End;

	FVector Direction = End - Start;
	Direction.Normalize();
	FQuat Orientation = FQuat::FindBetween(FVector(0.0f, 0.0f, 1.0f), Direction);
	FRotator Rotation(Orientation);

	int BottomIndex = -1;
	int TopIndex = -1;
	int SideIndex = -1;

	for (int i = 1; i < Resolution + 1; ++i) {
		float X = FMath::Cos(FMath::DegreesToRadians((i - 1)) * 360 / Resolution) * Radius;
		float Y = FMath::Sin(FMath::DegreesToRadians((i - 1)) * 360 / Resolution) * Radius;
		FVector Bottom = Rotation.RotateVector(FVector(X, Y, 0.0f)) + Start;
		FVector Top = Rotation.RotateVector(FVector(X, Y, 0.0f)) + End;
		Vertices[i + VertexOffset] = Bottom;
		Vertices[i + VertexOffset + 1 + Resolution] = Top;

		// Bottom face
		BottomIndex = (i - 1) * 3 + TriangleOffset;
		Triangles[BottomIndex + 0] = VertexOffset;
		Triangles[BottomIndex + 1] = VertexOffset + i;
		Triangles[BottomIndex + 2] = VertexOffset + i + 1;
		if (i == Resolution) {
			Triangles[BottomIndex + 2] = VertexOffset + 1;
		}

		// Top face
		TopIndex = (i - 1) * 3 + 3 * Resolution + TriangleOffset;
		Triangles[TopIndex + 0] = VertexOffset + Resolution + 2 + i;
		Triangles[TopIndex + 1] = VertexOffset + Resolution + 1 + i;
		Triangles[TopIndex + 2] = VertexOffset + Resolution + 1;
		if (i == Resolution) {
			Triangles[TopIndex + 0] = VertexOffset + Resolution + 2;
		}

		//Side face
		SideIndex = (i - 1) * 6 + 6 * Resolution + TriangleOffset;
		Triangles[SideIndex + 0] = VertexOffset + i + Resolution + 1;
		Triangles[SideIndex + 1] = VertexOffset + i + 1;
		Triangles[SideIndex + 2] = VertexOffset + i;
		Triangles[SideIndex + 3] = VertexOffset + i + Resolution + 1;
		Triangles[SideIndex + 4] = VertexOffset + i + Resolution + 2;
		Triangles[SideIndex + 5] = VertexOffset + i + 1;
		if (i == Resolution) {
			Triangles[SideIndex + 1] = VertexOffset + 1;
			Triangles[SideIndex + 4] = VertexOffset + Resolution + 2;
			Triangles[SideIndex + 5] = VertexOffset + 1;
		}
	}
}