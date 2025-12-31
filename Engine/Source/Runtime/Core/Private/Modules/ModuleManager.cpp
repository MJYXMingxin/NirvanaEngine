#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

FModuleManager::~FModuleManager()
{
}

FModuleManager &FModuleManager::Get()
{
    static FModuleManager Instance;
    return Instance;
}