#include "timp/Facade.h"
#include "timp/PkgMgr.h"

namespace timp
{

void Facade::Clear()
{
	PkgMgr::Instance()->Clear();
}

}