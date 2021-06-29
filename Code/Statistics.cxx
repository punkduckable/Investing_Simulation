#include <cmath>

#include "Statistics.hxx"



std::vector<double> Statistics::Mean(
                      const double*  Lists,
                      const unsigned List_Length,
                      const unsigned Num_Lists) {

  // First, allocate a vector to hold the means.
  std::vector<double> Means(Num_Lists, 0);

  // Sum up each column of Lists. We store the sum of the ith column of Lists
  // in the ith element of Means.
  for(unsigned i = 0; i < List_Length; i++) {
    for(unsigned j = 0; j < Num_Lists; j++) {
      Means[j] += Lists[i*Num_Lists + j];
    } // for(unsigned j = 0; j < Num_Lists; j++) {
  } // for(unsigned i = 0; i < List_Length; i++) {

  // Now divide each sum by the list length, yielding the averages.
  for(unsigned j = 0; j < Num_Lists; j++) { Means[j] /= List_Length; }

  // All done!
  return Means;
} // std::vector<double> Statistics::Mean(



std::vector<double> Statistics::Standard_Deviation(
                        const double*  Lists,
                        const unsigned List_Length,
                        const unsigned Num_Lists,
                        const std::vector<double> & Means) {

  // Allocate a vector to hold the Standard Deviation.
  std::vector<double> Standard_Deviations(Num_Lists, 0);

  // The standard deviation of a sequence {x_n}_{n = 1}^{N} with mean mu is
  // given by
  //        (sum_{i = 1}^{N} (x_n - mu)^2 / N)^(1/2)
  for(unsigned i = 0; i < List_Length; i++) {
    for(unsigned j = 0; j < Num_Lists; j++) {
      Standard_Deviations[j] += Lists[i*Num_Lists + j]*Lists[i*Num_Lists + j];
    } // for(unsigned j = 0; j < Num_Lists; j++) {
  } // for(unsigned i = 0; i < List_Length; i++) {

  for(unsigned j = 0; j < Num_Lists; j++) {
    Standard_Deviations[j] = std::sqrt(Standard_Deviations[j]/((double)List_Length));
  } // for(unsigned j = 0; j < Num_Lists; j++) {

  return Standard_Deviations;
} // std::vector<double> Statistics::Standard_Deviation(
