#ifndef BASE_H
#define BASE_H

#include "definitions.h"

class IConstraint
{
public:
	virtual long double error() = 0;
	virtual long double differential() = 0;
	virtual V::TConstraint type() const = 0;
	virtual long double value() const = 0;
};

#endif