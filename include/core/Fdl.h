#ifndef __FDL_FDL_H
#define __FDL_FDL_H

#include <thread>
#include <core\grid.hpp>
#include <core\fluidsolver.h>

namespace fdl {

/*
	This is a singleton object. From here you can 
	access all the FDL functionality
*/

class Fdl
{
public:
	static Fdl &Instance();
	~Fdl();

	// set the dimensions of the grid
	void setGridDimenctions(unsigned x, unsigned y, unsigned z, float dx);
	// set the tolerance
	void setCGTolerance(float tol);
	// set the maximum iterations
	void setCGMaxIterations(unsigned it);
	// set the time step
	void setStep(float step);

	void start();
	void startAsync();
	void stop();

protected:
	void solverFunc();

	Grid* m_macGrid;
	FluidSolver* m_fluidSolver;

	float m_cgTolerance;
	float m_step;
	unsigned m_cgMaxIterations;
	unsigned m_gridDimensions[3];
	float m_dx;

	bool m_stop;
	bool m_isRunning;

	std::thread m_runnerThread;

private:
	Fdl();
	Fdl(const Fdl &);
	void operator=(const Fdl &);
};

} // namespace fdl

#endif // FDL_FDL_H

