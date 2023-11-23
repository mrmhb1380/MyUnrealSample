// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomTestPlugin.h"
#include "CustomTestPluginStyle.h"
#include "CustomTestPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName CustomTestPluginTabName("CustomTestPlugin");

#define LOCTEXT_NAMESPACE "FCustomTestPluginModule"

void FCustomTestPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomTestPluginStyle::Initialize();
	FCustomTestPluginStyle::ReloadTextures();

	FCustomTestPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomTestPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FCustomTestPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomTestPluginModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CustomTestPluginTabName, FOnSpawnTab::CreateRaw(this, &FCustomTestPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FCustomTestPluginTabTitle", "CustomTestPlugin"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FCustomTestPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCustomTestPluginStyle::Shutdown();

	FCustomTestPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomTestPluginTabName);
}

TSharedRef<SDockTab> FCustomTestPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCustomTestPluginModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CustomTestPlugin.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FCustomTestPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CustomTestPluginTabName);
}

void FCustomTestPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCustomTestPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCustomTestPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomTestPluginModule, CustomTestPlugin)