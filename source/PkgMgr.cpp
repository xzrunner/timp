#include "PkgMgr.h"
#include "Package.h"

namespace timp
{

SINGLETON_DEFINITION(PkgMgr);

PkgMgr::PkgMgr()
{
}

PkgMgr::~PkgMgr()
{
	std::map<int, Package*>::iterator itr = m_packages.begin();
	for ( ; itr != m_packages.end(); ++itr) {
		delete itr->second;
	}
}

bool PkgMgr::Add(Package* pkg, int id)
{
	std::pair<std::map<int, Package*>::iterator, bool> ret 
		= m_packages.insert(std::make_pair(id, pkg));
	return ret.second;
}

const Package* PkgMgr::Query(int id) const
{
	std::map<int, Package*>::const_iterator itr = m_packages.find(id);
	if (itr != m_packages.end()) {
		return itr->second;
	} else {
		return NULL;
	}
}

}