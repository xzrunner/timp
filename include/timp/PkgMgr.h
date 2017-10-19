#ifndef _TIMP_PKG_MGR_H_
#define _TIMP_PKG_MGR_H_

#include "TIMP_Package.h"

#include <cu/uncopyable.h>
#include <cu/cu_macro.h>
#include <cu/cu_stl.h>

namespace timp
{

class PkgMgr : private cu::Uncopyable
{
public:
	bool Add(PackagePtr& pkg, int id);
	void Delete(int pkg);

	const Package* Query(int id) const;

	void Clear();

private:
	CU_MAP<int, PackagePtr> m_packages;

	CU_SINGLETON_DECLARATION(PkgMgr);

}; // PkgMgr

}

#endif // _TIMP_PKG_MGR_H_