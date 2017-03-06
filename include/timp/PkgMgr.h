#ifndef _TIMP_PKG_MGR_H_
#define _TIMP_PKG_MGR_H_

#include <CU_Uncopyable.h>
#include <CU_Singleton.h>

#include <map>

namespace timp
{

class Package;

class PkgMgr : private cu::Uncopyable
{
public:
	bool Add(Package* pkg, int id);
	const Package* Query(int id) const;

	void Clear();

private:
	std::map<int, Package*> m_packages;

	SINGLETON_DECLARATION(PkgMgr);

}; // PkgMgr

}

#endif // _TIMP_PKG_MGR_H_