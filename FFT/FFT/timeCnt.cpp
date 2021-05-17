#include "timeCnt.h"

timeCnt::timeCnt()
{

}
timeCnt::~timeCnt()
{

}
void timeCnt::Tic()
{
	prevtim = clock();
}
void  timeCnt::Toc()
{
	clock_t posttim = clock();
	double elapsed_time = (posttim - prevtim) / (double)CLOCKS_PER_SEC;
	std::cout << "Elapsed time: " << elapsed_time << std::endl;
}