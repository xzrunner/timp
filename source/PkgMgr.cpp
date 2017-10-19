#include "PkgMgr.h"
#include "TIMP_Package.h"

namespace timp
{

CU_SINGLETON_DEFINITION(PkgMgr);

PkgMgr::PkgMgr()
{
}

bool PkgMgr::Add(PackagePtr& pkg, int id)
{
	auto ret = m_packages.insert(std::make_pair(id, std::move(pkg)));
	return ret.second;
}

void PkgMgr::Delete(int pkg)
{
	auto itr = m_packages.find(pkg);
	if (itr != m_packages.end()) {
		m_packages.erase(itr);
	}
}

const Package* PkgMgr::Query(int id) const
{
	auto itr = m_packages.find(id);
	if (itr != m_packages.end()) {
		return itr->second.get();
	} else {
		return NULL;
	}
}

void PkgMgr::Clear()
{
	m_packages.clear();
}

}