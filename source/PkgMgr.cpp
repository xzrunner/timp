#include "PkgMgr.h"
#include "TIMP_Package.h"

namespace timp
{

SINGLETON_DEFINITION(PkgMgr);

PkgMgr::PkgMgr()
	: m_release_tag(false)
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
	if (ret.second && m_release_tag) {
		m_pkg_tag.push_back(id);
	}
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

void PkgMgr::Clear()
{
	std::map<int, Package*>::iterator itr = m_packages.begin();
	for ( ; itr != m_packages.end(); ++itr) {
		delete itr->second;
	}
	m_packages.clear();
}

void PkgMgr::SetReleaseTag()
{
	m_release_tag = true;
}

void PkgMgr::ReleaseAfterLastTag()
{
	for (int i = 0, n = m_pkg_tag.size(); i < n; ++i) {
		std::map<int, Package*>::iterator itr = m_packages.find(m_pkg_tag[i]);
		delete itr->second;
		m_packages.erase(itr);
	}
	m_pkg_tag.clear();
	m_release_tag = false;
}

}