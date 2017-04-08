#ifndef _TIMP_PKG_MGR_H_
#define _TIMP_PKG_MGR_H_

#include <CU_Uncopyable.h>
#include <CU_Singleton.h>

#include <map>
#include <vector>

namespace timp
{

class Package;

class PkgMgr : private cu::Uncopyable
{
public:
	bool Add(Package* pkg, int id);
	void Delete(int pkg);

	const Package* Query(int id) const;

	void Clear();

	void SetReleaseTag();
	void ReleaseAfterLastTag();

private:
	std::map<int, Package*> m_packages;

	bool m_release_tag;
	std::vector<int> m_pkg_tag;

	SINGLETON_DECLARATION(PkgMgr);

}; // PkgMgr

}

#endif // _TIMP_PKG_MGR_H_