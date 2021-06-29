#ifndef STATISTICS_HXX
#define STATISTICS_HXX

#include <vector>

namespace Statistics {

  std::vector<double> Mean(
                        const double* Lists,
                        const unsigned List_Length,
                        const unsigned Num_Lists);

  std::vector<double> Standard_Deviation(
                        const double*  Lists,
                        const unsigned List_Length,
                        const unsigned Num_Lists,
                        const std::vector<double> & Means);

} // namespace Statistics {

#endif
