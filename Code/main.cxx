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

  // Report initial balance
  printf("Initial balances...\n");
  My_Portfolio.Print_Balances();
  printf("\n");

  // Simualate future quarters using past data!
  Simulate::Quarters(Settings::Num_Quarters,
                     My_Portfolio,
                     Past_Stock_Returns,
                     Past_Bond_Returns);

  // Report final balance
  printf("Final balances...\n");
  My_Portfolio.Print_Balances();
  printf("\n");

  return 0;
} // int main(void) {
