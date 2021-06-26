#include <cstdio>
#include <vector>

#include "Portfolio.hxx"
#include "Reader.hxx"
#include "Returns.hxx"
#include "Simulate.hxx"

#include "Reader.cxx"


int main(void) {
  std::vector<Returns::Quarterly> Past_Returns = Reader::Read_Past_Returns("../Data/VTSAX.csv");

  int Length = (int)Past_Returns.size();
  std::printf("Number of past returns = %d\n", Length);

  for(int i = 0; i < Length; i++) {
    std::printf("%7.4lf, %7.4lf\n",
                Past_Returns[i].Capital_Gains,
                Past_Returns[i].Current_Income);
  } // for(int i = 0; i < 10; i++) {

  Portfolio My_Portfolio{ .7,
                          .25,
                          .05,
                          10000.,
                          1000.,
                          2000.,
                          7000.,
                          1.,
                          .80,
                          4};

  std::printf("Quarters_Between_Rebalancing = %d\n", My_Portfolio.Get_Quarters_Between_Rebalancing());
  My_Portfolio.Print_Balances();
  My_Portfolio.Update(Past_Returns[0], Past_Returns[1]);
  My_Portfolio.Print_Balances();
  My_Portfolio.Rebalance();
  My_Portfolio.Print_Balances();
  My_Portfolio.Print();

  return 0;
} // int main(void) {
