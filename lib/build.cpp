#include "build.h"

bool Recalculator::BuildFigureGoldMethod()
{
	// small value
	const double f_epsi = 1e-15;

	if (constraint->error() < f_epsi) return false;

	const uint vars_count = pointers.size();

	ldoub* start_para = new ldoub[vars_count];
	for (uint i = 0; i < vars_count; i++)
	{
		start_para[i] = *pointers[i];
	}
	
	// great value
	const ldoub f_Epsi = 1e+6;

	// amount of iterations
	uint f_count = 0;

	// current value of function
	ldoub f_current = constraint->error();

	// value of function on previous iteration
	ldoub f_prev = 0;

	// gradient of function
	ldoub *grad = new ldoub[vars_count];

	// value of parameters on previous iteration
	ldoub *old_para = new ldoub[vars_count];

	do
	{
		f_count++;
		f_prev = f_current;
		for (uint k = 0; k < vars_count; k++)
			grad[k] = constraint->differential(pointers[k]);

		double a1 = 1;

		for (uint k = 0; k < vars_count; k++)
			old_para[k] = *pointers[k];

		for (uint k = 0; k < vars_count; k++)
			*pointers[k] -= a1*grad[k];

		ldoub f_a1 = constraint->error();

		while (f_a1 <= f_prev)
		{
			a1 *= 2; // 1.5
			for (uint k = 0; k < vars_count; k++)
				*pointers[k] = old_para[k] - a1*grad[k];
			f_a1 = constraint->error();
		}
		// ratio of the golden section
		const ldoub gold = 0.5 + sqrt(5.0 / 4);

		ldoub a0 = 0;
		ldoub f_a0 = f_prev;
		ldoub aleft = a1 - (a1 - a0) / gold;
		ldoub aright = a0 + (a1 - a0) / gold;

		for (uint k = 0; k < vars_count; k++)
			*pointers[k] = old_para[k] - aleft*grad[k];

		double f_al = constraint->error();

		for (uint k = 0; k < vars_count; k++)
			*pointers[k] = old_para[k] - aright*grad[k];

		ldoub f_ar = constraint->error();

		// amount of interations of the golden section
		uint gold_count = 0;

		while (abs(f_al - f_ar) > f_epsi && gold_count < f_Epsi)
		{
			gold_count++;
			if (f_al < f_ar)
			{
				a1 = aright; f_a1 = f_ar;
				aright = aleft; f_ar = f_al;
				aleft = a1 - (a1 - a0) / gold;
				for (uint k = 0; k < vars_count; k++)
					*pointers[k] = old_para[k] - aleft*grad[k];
				f_al = constraint->error();
			}
			else
			{
				a0 = aleft; f_a0 = f_al;
				aleft = aright; f_al = f_ar;
				aright = a0 + (a1 - a0) / gold;

				for (uint k = 0; k < vars_count; k++)
					*pointers[k] = old_para[k] - aright*grad[k];
				f_ar = constraint->error();
			}
		}

		for (uint k = 0; k < vars_count; k++)
			*pointers[k] = old_para[k] - (aright + aleft) / 2 * grad[k];
		f_current = constraint->error();

	} while (abs(f_prev - f_current) > f_epsi && f_count < f_Epsi && f_current > f_epsi);
	delete[] grad;
	delete[] old_para;
	delete[] start_para;
	return f_current > f_epsi ? true : false; // can't build?
}

void Recalculator::Calculate()
{
	std::vector<ldoub> start_parameters;
	for (std::vector<ldoub*>::iterator i = pointers.begin(); i != pointers.end(); i++)
	{
		start_parameters.push_back(**i);
	}
	if (BuildFigureGoldMethod()) // if can't build
	{
		throw V::Error("Can't build figure");
	}
}

#undef ldoub
#undef uint