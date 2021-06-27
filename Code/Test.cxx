#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Portfolio.hxx"
#include "Returns.hxx"
#include "Simulate.hxx"

#include "Simulate.cxx"


namespace Test {
  void Portfolio_Class(void);
  void Simulate(void);
} // namespace Test {


void Test::Portfolio_Class(void) {
  // Fist, initialize a portfolio object.
  const double Target_Stock = .7;
  const double Target_Bond  = .25;
  const double Target_Cash  = .05;

  const double Balance_Stock = 10000.;
  const double Balance_Bond  = 1000.;
  const double Balance_Cash  = 2000.;

  const double Quarterly_Deposit_Rate = 7000.;

  const double Dividend_Reinvestment_Rate = .95;
  const double Interest_Reinvestment_Rate = .8;

  const unsigned Quarters_Between_Rebalancing = 4;

  Portfolio My_Portfolio{Target_Stock,
                         Target_Bond,
                         Target_Cash,
                         Balance_Stock,
                         Balance_Bond,
                         Balance_Cash,
                         Quarterly_Deposit_Rate,
                         Dividend_Reinvestment_Rate,
                         Interest_Reinvestment_Rate,
                         Quarters_Between_Rebalancing};

  // Check that it was initialized correctly.
  assert(My_Portfolio.Get_Quarters_Between_Rebalancing() == Quarters_Between_Rebalancing);
  assert(My_Portfolio.Get_Balance_Stock() == Balance_Stock);
  assert(My_Portfolio.Get_Balance_Bond()  == Balance_Bond);
  assert(My_Portfolio.Get_Balance_Cash()  == Balance_Cash);
  assert(My_Portfolio.Get_Balance() == Balance_Stock + Balance_Bond + Balance_Cash);

  // Generate random returns.
  std::srand(std::time(NULL));
  Returns::Quarterly Returns;
  double Rand_Capital_Gains = ((double)std::rand())/((double)RAND_MAX);
  double Rand_Interest      = ((double)std::rand())/((double)RAND_MAX);
  Returns.Capital_Gains  = Rand_Capital_Gains;
  Returns.Current_Income = Rand_Interest;

  // Use these random returns to update the Portfolio.
  My_Portfolio.Update(Returns, Returns);

  // Check that the new balance matches what we think it should be.
  double Projected_Stock_Balance = (Balance_Stock*(1. + Rand_Capital_Gains))*
                                   (1. + Rand_Interest*Dividend_Reinvestment_Rate) +
                                   (Quarterly_Deposit_Rate*Target_Stock);
  double Projected_Bond_Balance  = (Balance_Bond*(1. + Rand_Capital_Gains))*
                                   (1. + Rand_Interest*Interest_Reinvestment_Rate) +
                                   (Quarterly_Deposit_Rate*Target_Bond);
  double Projected_Cash_Balance  =
            (Balance_Cash +
            (Balance_Stock*(1. + Rand_Capital_Gains))*Rand_Interest*(1. - Dividend_Reinvestment_Rate) +
            (Balance_Bond *(1. + Rand_Capital_Gains))*Rand_Interest*(1. - Interest_Reinvestment_Rate) +
            (Quarterly_Deposit_Rate*Target_Cash));

  double Projected_Balance = Projected_Stock_Balance + Projected_Bond_Balance + Projected_Cash_Balance;

  std::printf("Actual = %lf, Projected = %lf\n", My_Portfolio.Get_Balance_Stock(), Projected_Stock_Balance);

  double epsilon = 1e-10;
  assert(std::abs(My_Portfolio.Get_Balance_Stock() - Projected_Stock_Balance) < epsilon);
  assert(std::abs(My_Portfolio.Get_Balance_Bond()  - Projected_Bond_Balance ) < epsilon);
  assert(std::abs(My_Portfolio.Get_Balance_Cash()  - Projected_Cash_Balance ) < epsilon);
  assert(std::abs(My_Portfolio.Get_Balance()       - Projected_Balance      ) < epsilon);
} // void Test::Portfolio(void) {



void Test::Simulate(void) {
  // To do?
} // void Test::Simulate(void) {



int main() {
  Test::Portfolio_Class();

  return 0;
} // int main() {
