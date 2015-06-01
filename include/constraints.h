#pragma once

#include "base.h"
#include <vector>

class ConstraintCollector :public IConstraint
{

private:
	std::vector<IConstraint*> _storage;
public:
	virtual ~ConstraintCollector()
	{

	}
	void add(IConstraint *c)
	{
		if (c) _storage.push_back(c);
	}
	virtual ldoub error()
	{
		ldoub err = 0;
		for (uint k = 0; k < _storage.size(); ++k)
			err += _storage[k]->error();
		return err;
	};
	virtual ldoub differential(ldoub* par)
	{
		ldoub res = 0;
		for (uint k = 0; k < _storage.size(); ++k)
			res += _storage[k]->differential(par);
		return res;
	}
	virtual V::TConstraint type() const
	{
		return V::Collector;
	}
	virtual ldoub value() const
	{
		return NAN;
	}
};