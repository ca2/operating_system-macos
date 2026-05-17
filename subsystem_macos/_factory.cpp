//
// Created by camilo on 2026-04-04.
//
#include "framework.h"
#include "platform/subsystem.h"
#include "thread/GlobalMutex.h"
#include "thread/Thread.h"
#include "node/DynamicLibrary.h"
#include "node/NamedPipe.h"
#include "node/OperatingSystem.h"
#include "node/OperatingSystemApplication.h"
#include "node/OperatingSystemHook.h"
#include "node/Pipe.h"
#include "node/Shell.h"
#include "node/SystemInformation.h"
#include "node/Clipboard.h"
#include "node/Clipboard2.h"
#include "node/Displays.h"
#include "node/Impersonator.h"
#include "node/InputInjector.h"
#include "node/PipeClient.h"
#include "node/Screen.h"
#include "node/PipeImpersonatedThread.h"
#include "node/security/SecurityAttributes.h"
#include "node/PipeServer.h"
#include "node/Process.h"
#include "node/VersionInfo.h"
#include "subsystem/node/VersionInfo.h"
#include "thread/DesktopSelector.h"
#include "thread/ZombieKiller.h"
#include "thread/ThreadCollector.h"


DECLARE_FACTORY(subsystem_bsd_sockets);
   

IMPLEMENT_FACTORY(subsystem_macos)
{

   subsystem_bsd_sockets_factory(pfactory);

   pfactory->add_factory_item<::subsystem_macos::GlobalMutex, ::subsystem::GlobalMutexInterface>();
   //pfactory->add_factory_item<::subsystem_macos::Thread, ::subsystem::ThreadInterface>();
   pfactory->add_factory_item<::subsystem_macos::Shell, ::subsystem::Shell>();
//   pfactory->add_factory_item<::subsystem_macos::SecurityAttributes, ::subsystem::SecurityAttributesInterface>();
   pfactory->add_factory_item<::subsystem_macos::PipeServer, ::subsystem::PipeServer>();
   pfactory->add_factory_item<::subsystem_macos::Process, ::subsystem::ProcessInterface>();
   pfactory->add_factory_item<::subsystem_macos::ZombieKiller, ::subsystem::ZombieKiller>();
   pfactory->add_factory_item<::subsystem_macos::PipeClient, ::subsystem::PipeClientInterface>();
   pfactory->add_factory_item<::subsystem_macos::NamedPipe, ::subsystem::NamedPipeInterface>();
   pfactory->add_factory_item<::subsystem_macos::Pipe, ::subsystem::PipeInterface>();
   pfactory->add_factory_item<::subsystem_macos::ThreadCollector, ::subsystem::ThreadCollector>();
   pfactory->add_factory_item<::subsystem_macos::PipeImpersonatedThread, ::subsystem::PipeImpersonatedThreadInterface>();
   pfactory->add_factory_item<::subsystem_macos::VersionInfo, ::subsystem::VersionInfoInterface>();
   pfactory->add_factory_item<::subsystem_macos::Displays, ::subsystem::DisplaysInterface>();
   pfactory->add_factory_item<::subsystem_macos::DynamicLibrary, ::subsystem::DynamicLibraryInterface>();
   pfactory->add_factory_item<::subsystem_macos::Screen, ::subsystem::ScreenInterface>();
   pfactory->add_factory_item<::subsystem_macos::InputInjector, ::subsystem::InputInjectorInterface>();
   pfactory->add_factory_item<::subsystem_macos::Clipboard2, ::subsystem::Clipboard2>();
   pfactory->add_factory_item<::subsystem_macos::Impersonator, ::subsystem::ImpersonatorInterface>();


   pfactory->add_factory_item<::subsystem_macos::subsystem, ::subsystem::subsystem>();
   pfactory->add_factory_item<::subsystem_macos::SystemInformation, ::subsystem::SystemInformationInterface>();
   pfactory->add_factory_item<::subsystem_macos::OperatingSystem,
                              ::subsystem::OperatingSystem>();
   pfactory->add_factory_item<::subsystem_macos::OperatingSystemApplication, ::subsystem::OperatingSystemApplicationInterface>();
   pfactory->add_factory_item<::subsystem_macos::OperatingSystemHook,
                              ::subsystem::OperatingSystemHookInterface>();

   pfactory->add_factory_item<::subsystem_macos::DesktopSelector, ::subsystem::DesktopSelector>();
   pfactory->add_factory_item<::subsystem_macos::Clipboard, ::subsystem::ClipboardInterface>();

}


