#include <cstdlib>
#include <ctime>
#include <cstdio>

#include "Simulate.hxx"



void Simulate::Quarter(Portfolio & Portfolio,
                       const std::vector<Returns::Quarterly> & Stock_Return_Samples,
                       const std::vector<Returns::Quarterly> & Bond_Return_Samples) {

  // First, determine how many Stock, Bond samples we have
  const unsigned Num_Stock_Samples = Stock_Return_Samples.size();
  const unsigned Num_Bond_Samples  = Bond_Return_Samples.size();

  // Now, randomly select a stock, bond sample.
  const unsigned Stock_Index = std::rand() % Num_Stock_Samples;
  const unsigned Bond_Index  = std::rand() % Num_Bond_Samples;
  Returns::Quarterly Stock_Return = Stock_Return_Samples[Stock_Index];
  Returns::Quarterly Bond_Return  = Bond_Return_Samples [Bond_Index ];

  // Update the Portfolio according to these samples.
  Portfolio.Update(Stock_Return, Bond_Return);
} // void Simulate::Quarter(Portfolio Portfolio,..



void Simulate::Quarters(const unsigned Num_Quarters,
                        Portfolio & Portfolio,
                        const std::vector<Returns::Quarterly> & Stock_Return_Samples,
                        const std::vector<Returns::Quarterly> & Bond_Return_Samples) {

  // First, seed the random number generator.
  std::srand(std::time(NULL));

  // Now loop through the quarters.
  for(unsigned i = 0; i < Num_Quarters; i++) {
    Simulate::Quarter(Portfolio,
                      Stock_Return_Samples,
                      Bond_Return_Samples);
  } // for(unsigned i = 0; i < Num_Quarters; i++) {
} // void Simulate::Quarters(const unsigned Num_Quarters,
