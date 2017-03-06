#include "TIMP_Facade.h"
#include "PkgMgr.h"

namespace timp
{

void Facade::Clear()
{
	PkgMgr::Instance()->Clear();
}

}