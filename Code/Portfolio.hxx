#ifndef PORTFOLIO_HXX
#define PORTFOLIO_HXX

#include <cstdio>
#include <assert.h>

#include "Returns.hxx"


class Portfolio {
  private:
    // What proportion of our portfolio should be in stock, bonds, and cash?
    // We will rebalance the portfolio periodically.
    double Target_Stock;
    double Target_Bond;
    double Target_Cash;

    double Balance_Stock;
    double Balance_Bond;
    double Balance_Cash;

    // How much fresh $ we inject into the portfolio after each quarter. This
    // $ will be added to the Stock, Bond, and Cash balances in proportions
    // specified by the targets.
    double Quarterly_Deposit_Rate;

    // Stocks (as dividends) and bonds (as interest) give current income. These
    // variables specify what propotion of that current income we should
    // reinvest. Reinvested $ is automatically injected into the asset class
    // that produced it.
    double Dividend_Reinvestment_Rate;
    double Interest_Reinvestment_Rate;

    // This basically specifies how frequently we rebalance the portfolio so
    // that the % of the portfolio's $ in each asset class matches the targets.
    unsigned Quarters_Between_Rebalancing;
    unsigned Quarters_Since_Rebalancing = 0;
  public:
    Portfolio(const double   Target_Stock,
              const double   Target_Bond,
              const double   Target_Cash,
              const double   Initial_Balance_Stock,
              const double   Initial_Balance_Bond,
              const double   Initial_Balance_Cash,
              const double   Quarterly_Deposit_Rate,
              const double   Dividend_Reinvestment_Rate,
              const double   Interest_Reinvestment_Rate,
              const unsigned Quarters_Between_Rebalancing) :

              Target_Stock  (Target_Stock),
              Target_Bond   (Target_Bond),
              Target_Cash   (Target_Cash),
              Balance_Stock (Initial_Balance_Stock),
              Balance_Bond  (Initial_Balance_Bond),
              Balance_Cash  (Initial_Balance_Cash),
              Quarterly_Deposit_Rate      (Quarterly_Deposit_Rate),
              Dividend_Reinvestment_Rate  (Dividend_Reinvestment_Rate),
              Interest_Reinvestment_Rate  (Interest_Reinvestment_Rate),
              Quarters_Between_Rebalancing(Quarters_Between_Rebalancing)
    {
      // Check that targets are non-negative.
      assert ((*this).Target_Stock >= 0.);
      assert ((*this).Target_Bond  >= 0.);
      assert ((*this).Target_Cash  >= 0.);

      // Check that targets sum to 1.
      assert ((*this).Target_Stock + (*this).Target_Bond + (*this).Target_Cash == 1.);

      // Check that initial balances are non-negative
      assert ((*this).Balance_Stock >= 0.);
      assert ((*this).Balance_Bond >= 0.);
      assert ((*this).Balance_Cash >= 0.);

      // Check that Reinvestement rates are between 0 and 1.
      assert((*this).Dividend_Reinvestment_Rate >= 0.);
      assert((*this).Interest_Reinvestment_Rate >= 0.);
      assert((*this).Dividend_Reinvestment_Rate <= 1.);
      assert((*this).Interest_Reinvestment_Rate <= 1.);

      // Check that Quarters Between Rebalancing is positive.
      assert((*this).Quarters_Between_Rebalancing > 0);
    } // Portfolio(const double   Target_Stock,...



    unsigned Get_Quarters_Between_Rebalancing(void) const {
      return (*this).Quarters_Between_Rebalancing;
    } // unsigned Get_Quarters_Between_Rebalancing(void) {

    double Get_Balance_Stock(void) const { return (*this).Balance_Stock; }
    double Get_Balance_Bond(void)  const { return (*this).Balance_Bond;  }
    double Get_Balance_Cash(void)  const { return (*this).Balance_Cash;  }

    double Get_Balance(void) const {
      return (*this).Balance_Stock + (*this).Balance_Bond + (*this).Balance_Cash;
    } // double Get_Balance(void) const {



    void Update(const Returns::Quarterly Stock,
                const Returns::Quarterly Bond) {
      // Update stock balance. All dividends that aren't reinvested become cash.
      (*this).Balance_Stock *= (1. + Stock.Capital_Gains);
      const double Dividends = (*this).Balance_Stock*Stock.Current_Income;
      (*this).Balance_Stock += Dividends*(*this).Dividend_Reinvestment_Rate;
      (*this).Balance_Cash +=  Dividends*(1. - (*this).Dividend_Reinvestment_Rate);

      // Update bond balance. All interest that aren't reinvested become cash.
      (*this).Balance_Bond *= (1. + Bond.Capital_Gains);
      const double Interest = (*this).Balance_Bond*Bond.Current_Income;
      (*this).Balance_Bond += Interest*(*this).Interest_Reinvestment_Rate;
      (*this).Balance_Cash += Interest*(1. - (*this).Interest_Reinvestment_Rate);

      // Now update based on quarterly deposit rate.
      (*this).Balance_Stock += (*this).Quarterly_Deposit_Rate*(*this).Target_Stock;
      (*this).Balance_Bond  += (*this).Quarterly_Deposit_Rate*(*this).Target_Bond;
      (*this).Balance_Cash  += (*this).Quarterly_Deposit_Rate*(*this).Target_Cash;

      // Check if we need to rebalance. If so, then do that now.
      (*this).Quarters_Since_Rebalancing++;
      if((*this).Quarters_Since_Rebalancing == (*this).Quarters_Between_Rebalancing) {
        (*this).Rebalance();
      } // if((*this).Quarters_Since_Rebalancing == (*this).Quarters_Between_Rebalancing) {
    } // void Update(Returns::Quarterly Stock,



    void Rebalance(void) {
      // First, determine the portfolio's current total balanace.
      const double Balance = (*this).Balance_Stock +
                             (*this).Balance_Bond +
                             (*this).Balance_Cash;

      // Now, reset the stock, bond, and cash balances based on the targets.
      (*this).Balance_Stock = Balance*(*this).Target_Stock;
      (*this).Balance_Bond  = Balance*(*this).Target_Bond;
      (*this).Balance_Cash  = Balance*(*this).Target_Cash;
    } // void Rebalance(void) {



    void Print_Balances(void) const {
      std::printf("Stock Balance = %10.2lf. Bond Balance = %10.2lf. Cash Balance = %10.2lf. Total = %10.2lf\n",
                  (*this).Balance_Stock,
                  (*this).Balance_Bond,
                  (*this).Balance_Cash,
                  (*this).Balance_Stock + (*this).Balance_Bond + (*this).Balance_Cash);
    } // void Print_Balances(void) const {



    void Print(void) const {
      std::printf("Target_Stock  = %lf\n",   (*this).Target_Stock);
      std::printf("Target_Bond   = %lf\n",   (*this).Target_Bond);
      std::printf("Target_Cash   = %lf\n\n", (*this).Target_Cash);

      std::printf("Balance_Stock = %lf\n",   (*this).Balance_Stock);
      std::printf("Balance_Bond  = %lf\n",   (*this).Balance_Bond);
      std::printf("Balance_Cash  = %lf\n\n", (*this).Balance_Cash);

      std::printf("Quarterly Deposit rate      = %lf\n",   (*this).Quarterly_Deposit_Rate);
      std::printf("Dividend Reinvestement Rate = %lf\n",   (*this).Dividend_Reinvestment_Rate);
      std::printf("Interest Reinvestement Rate = %lf\n\n", (*this).Dividend_Reinvestment_Rate);

      std::printf("Quarters Between Rebalancing = %d\n", (*this).Quarters_Between_Rebalancing);
    } // void Print(void) {
};

#endif
