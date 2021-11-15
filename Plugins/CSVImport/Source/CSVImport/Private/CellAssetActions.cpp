

#include "CellAssetActions.h"

#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "CellDataFactory.h"
#include "CellMesh.h"
#include "Styling/SlateStyle.h"



#define LOCTEXT_NAMESPACE "AssetTypeActions"


FCellAssetActions::FCellAssetActions(const TSharedRef<ISlateStyle>& InStyle)
	: Style(InStyle)
{ }


bool FCellAssetActions::CanFilter()
{
	return false;
}


uint32 FCellAssetActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}


FText FCellAssetActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_Cell", "Cell");
}


UClass* FCellAssetActions::GetSupportedClass() const
{
	return nullptr;// UCellMesh::StaticClass();
}


FColor FCellAssetActions::GetTypeColor() const
{
	return FColor::White;
}


bool FCellAssetActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return false;
}


#undef LOCTEXT_NAMESPACE