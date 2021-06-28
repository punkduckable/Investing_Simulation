#include <cstdio>
#include <vector>
#include <string>

#include "./IO/Data_Reader.hxx"
#include "./IO/IO_Ops.hxx"
#include "./IO/Settings_Parser.hxx"
#include "Portfolio.hxx"
#include "Returns.hxx"
#include "Simulate.hxx"

#include "./IO/Data_Reader.cxx"
#include "./IO/IO_Ops.cxx"
#include "./IO/Settings_Parser.cxx"
#include "Simulate.cxx"



int main(void) {
  // First, read the settings file.
  Settings::Parser::Read();
  printf("Read the following settings...\n");
  Settings::Print();
  printf("\n");

  // Now, load the past returns
  std::string Stock_File_Path = "../Data/" + Settings::Past_Stock_Returns_File;
  std::string Bond_File_Path  = "../Data/" + Settings::Past_Bond_Returns_File;

  std::vector<Returns::Quarterly> Past_Stock_Returns = Reader::Read_Past_Returns(Stock_File_Path.c_str());
  std::vector<Returns::Quarterly> Past_Bond_Returns  = Reader::Read_Past_Returns(Bond_File_Path.c_str());

  /*
  int Length = (int)Past_Stock_Returns.size();
  std::printf("Number of past stock returns = %d\n", Length);

  for(int i = 0; i < Length; i++) {
    std::printf("%7.4lf, %7.4lf\n",
                Past_Stock_Returns[i].Capital_Gains,
                Past_Stock_Returns[i].Current_Income);
  } // for(int i = 0; i < 10; i++) {
  */

  // Initialize the Portfolio using the settings!
  Portfolio My_Portfolio{ Settings::Target_Stock,
                          Settings::Target_Bond,
                          Settings::Target_Cash,
                          Settings::Initial_Balance_Stock,
                          Settings::Initial_Balance_Bond,
                          Settings::Initial_Balance_Cash,
                          Settings::Quarterly_Deposit_Rate,
                          Settings::Dividend_Reinvestment_Rate,
                          Settings::Interest_Reinvestment_Rate,
                          Settings::Quarters_Between_Rebalancing};

  // Initialize vector to hold simulation results. Columns 0, 1, 2, and 3 will
  // hold the Stock, Bond, Cash, and total balances, respectively, of each
  // simulation. The ith row corresponds to the results of the ith simulation.
  // The array is stored in row major order.
  double* Balances = new double[4*Settings::Num_Simulations];

  // Run the simulations!
  std::printf("Running %u simulations...", Settings::Num_Simulations);
  for(unsigned i = 0; i < Settings::Num_Simulations; i++) {
    // First, reset the Balances/Quarters_Since_Rebalancing
    My_Portfolio.Set_Balance_Stock(Settings::Initial_Balance_Stock);
    My_Portfolio.Set_Balance_Bond (Settings::Initial_Balance_Bond );
    My_Portfolio.Set_Balance_Cash (Settings::Initial_Balance_Cash );
    My_Portfolio.Set_Quarters_Since_Rebalancing(0);

    // Run a simulation.
    Simulate::Quarters(Settings::Num_Quarters,
                       My_Portfolio,
                       Past_Stock_Returns,
                       Past_Bond_Returns);

    // Store the balances in the corresponding elements of the Balances array.
    Balances[4*i + 0] = My_Portfolio.Get_Balance_Stock();
    Balances[4*i + 1] = My_Portfolio.Get_Balance_Bond();
    Balances[4*i + 2] = My_Portfolio.Get_Balance_Cash();
    Balances[4*i + 3] = My_Portfolio.Get_Balance();
  } // for(unsigned i = 0; i < Settings::Num_Simulations; i++) {
  std::printf("done!\n");

  // Determine statistics...
  double Avg_Balance_Stock = 0;
  double Avg_Balance_Bond = 0;
  double Avg_Balance_Cash = 0;
  double Avg_Balance = 0;

  for(unsigned i = 0; i < Settings::Num_Simulations; i++) {
    Avg_Balance_Stock += Balances[4*i + 0];
    Avg_Balance_Bond  += Balances[4*i + 1];
    Avg_Balance_Cash  += Balances[4*i + 2];
    Avg_Balance       += Balances[4*i + 3];
  } // for(unsigned i = 0; i < Settings::Num_Simulations; i++) {

  Avg_Balance_Stock /= (double)Settings::Num_Simulations;
  Avg_Balance_Bond  /= (double)Settings::Num_Simulations;
  Avg_Balance_Cash  /= (double)Settings::Num_Simulations;
  Avg_Balance       /= (double)Settings::Num_Simulations;

  // Report results.
  std::printf("Avg Stock balance = %lf\n", Avg_Balance_Stock);
  std::printf("Avg Bond  balance = %lf\n", Avg_Balance_Bond);
  std::printf("Avg Cash  balance = %lf\n", Avg_Balance_Cash);
  std::printf("Avg Balance       = %lf\n", Avg_Balance);

  // Delete Balance arry
  delete [] Balances;

  return 0;
} // int main(void) {
