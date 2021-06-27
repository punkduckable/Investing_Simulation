#ifndef SETTINGS_PARSER_HXX
#define SETTINGS_PARSER_HXX

#include <string>

namespace Settings {
  // Portfolio settings.
  double   Target_Stock;
  double   Target_Bond;
  double   Target_Cash;
  double   Initial_Balance_Stock;
  double   Initial_Balance_Bond;
  double   Initial_Balance_Cash;
  double   Quarterly_Deposit_Rate;
  double   Dividend_Reinvestment_Rate;
  double   Interest_Reinvestment_Rate;
  unsigned Quarters_Between_Rebalancing;

  // Simulation Settings
  unsigned Num_Quarters;
  unsigned Num_Simulations;

  // Data settings.
  std::string Past_Stock_Returns_File;
  std::string Past_Bond_Returns_File;

  void Print(void);

  namespace Parser {
    void Read(void);
  } // namespace Parser {
} // namespace Settings {

#endif
