#ifndef SIMULATE_HXX
#define SIMULATE_HXX

#include <vector>

#include "Portfolio.hxx"
#include "Returns.hxx"


namespace Simulate {

  void Quarter(Portfolio & Portfolio,
               const std::vector<Returns::Quarterly> & Stock_Return_Samples,
               const std::vector<Returns::Quarterly> & Bond_Return_Samples);

  void Quarters(const unsigned Num_Quarters,
                Portfolio & Portfolio,
                const std::vector<Returns::Quarterly> & Stock_Return_Samples,
                const std::vector<Returns::Quarterly> & Bond_Return_Samples);

} // namespace Simulate {

#endif
