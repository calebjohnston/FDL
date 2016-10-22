#include <core\Fdl.h>
#include <core\fluidsolver.h>
#include <core\grid.hpp>

#include <io/pngexporter.h>

#include <omp.h>

namespace fdl {

Fdl &Fdl::Instance()
{
	static Fdl inst;
	return inst;
}

Fdl::Fdl()
	:m_macGrid(NULL), m_fluidSolver(NULL), m_step(0.1f),
	m_cgMaxIterations(100), m_stop(false), m_isRunning(false)
{
	m_cgTolerance = (float)pow(FLT_EPSILON, 0.5);
	m_gridDimensions[0] = 50;
	m_gridDimensions[1] = 50;
	m_gridDimensions[2] = 50;
}

Fdl::~Fdl()
{
	delete m_fluidSolver;
	delete m_macGrid;
}

void Fdl::setGridDimenctions(unsigned x, unsigned y, unsigned z, float dx)
{
	m_gridDimensions[0] = x;
	m_gridDimensions[1] = y;
	m_gridDimensions[2] = z;
	m_dx = dx;
}

void Fdl::setCGTolerance(float tol)
{
	m_cgTolerance = tol;
}

void Fdl::setCGMaxIterations(unsigned it)
{
	m_cgMaxIterations = it;
}

void Fdl::setStep(float step)
{
	m_step = step;
}

void Fdl::startAsync()
{
	if (m_isRunning) return;

	m_macGrid = new fdl::Grid(m_gridDimensions[0], m_gridDimensions[1], m_gridDimensions[2], m_dx);
	m_fluidSolver = new fdl::FluidSolver(m_macGrid);
	m_fluidSolver->setCGTolerance(m_cgTolerance);
	m_fluidSolver->setCGMaxIter(m_cgMaxIterations);

	m_isRunning = true;
	m_runnerThread = std::thread(&Fdl::solverFunc, this);
}

void Fdl::start()
{
	if (m_isRunning) return;

	m_macGrid = new fdl::Grid(m_gridDimensions[0], m_gridDimensions[1], m_gridDimensions[2], m_dx);
	m_fluidSolver = new fdl::FluidSolver(m_macGrid);
	m_fluidSolver->setCGTolerance(m_cgTolerance);
	m_fluidSolver->setCGMaxIter(m_cgMaxIterations);

	m_isRunning = true;
	solverFunc();
}

void Fdl::stop()
{
	if (!m_isRunning) return;

	m_stop = true;
	m_runnerThread.join();
}

void Fdl::solverFunc()
{
	omp_set_num_threads(omp_get_num_procs());

	PngExporter* pngOut = new fdl::PngExporter("density_export_");
	unsigned totalIter = 0;

	std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

	while (!m_stop && totalIter < m_cgMaxIterations)
	{
		m_fluidSolver->step(m_step);
		pngOut->start(*m_macGrid);
		++totalIter;
	}

	std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();

	std::cout << "Finished in " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << std::endl;
}

} // namespace fdl