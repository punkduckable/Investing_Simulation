#include <cstdio>
#include <vector>

#include "Reader.hxx"
#include "Simulate.hxx"
#include "Returns.hxx"

#include "Reader.cxx"


int main(void) {
  std::vector<Returns::Quarterly> Past_Returns = Reader::Read_Past_Returns("../Data/VTSAX.csv");

  int Length = (int)Past_Returns.size();
  std::printf("Vector Length = %d\n", Length);

  for(int i = 0; i < Length; i++) {
    std::printf("%7.4lf, %7.4lf\n",
                Past_Returns[i].Capital_Gains,
                Past_Returns[i].Current_Income);
  } // for(int i = 0; i < 10; i++) {

  return 0;
} // int main(void) {
