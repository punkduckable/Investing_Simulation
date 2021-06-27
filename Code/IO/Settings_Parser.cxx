#include "Settings_Parser.hxx"
#include "IO_Ops.hxx"

#include <stdio.h>
#include <fstream>



void Settings::Print(void) {
  // Portfolio settings.
  printf("Target Stock =                    %lf\n", Target_Stock);
  printf("Target Bond  =                    %lf\n", Target_Bond);
  printf("Target Cash  =                    %lf\n", Target_Cash);

  printf("Initial Balance Stock =           %lf\n", Initial_Balance_Stock);
  printf("Initial Balance Bond  =           %lf\n", Initial_Balance_Bond);
  printf("Initial Balance Cash  =           %lf\n", Initial_Balance_Cash);

  printf("Quarterly Deposit Rate =          %lf\n", Quarterly_Deposit_Rate);
  printf("Dividend Reinvestement Rate =     %lf\n", Dividend_Reinvestment_Rate);
  printf("Interest Reinvestement Rate =     %lf\n", Interest_Reinvestment_Rate);

  printf("Quarters Between Rebalancing =    %d\n",  Quarters_Between_Rebalancing);

  // Data settings.
  printf("Past Stock Returns File =         %s\n",  Past_Stock_Returns_File.c_str());
  printf("Past Bond Returns File  =         %s\n",  Past_Bond_Returns_File. c_str());
} // void Settings::Print(void) {



void Settings::Parser::Read(void) {
  // Open the settings file!
  std::ifstream File;
  File.open("../Settings.txt");
  if(File.is_open() == false) {
    printf("Cant Open File! Thrown by Settings::Parser::Read.\n"
           "For some reasons, we couldn't open ../Settings.txt. Aborting\n");
    abort();
  } // if(File.is_open() == false) {

  // Set up buffers and then read the settings!
  std::string strBuf;



  //////////////////////////////////////////////////////////////////////////////
  // Portfolio Settings

  strBuf = IO::read_line_after(File, "Stock [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Target_Stock);

  strBuf = IO::read_line_after(File, "Bond [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Target_Bond);

  strBuf = IO::read_line_after(File, "Cash [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Target_Cash);


  strBuf = IO::read_line_after(File, "Initial Stock Balance [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Initial_Balance_Stock);

  strBuf = IO::read_line_after(File, "Initial Bond Balance [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Initial_Balance_Bond);

  strBuf = IO::read_line_after(File, "Initial Cash Balance [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Initial_Balance_Cash);


  strBuf = IO::read_line_after(File, "Quarterly Deposit Rate [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Quarterly_Deposit_Rate);


  strBuf = IO::read_line_after(File, "Dividend Reinvestment Rate [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Dividend_Reinvestment_Rate);

  strBuf = IO::read_line_after(File, "Interest Reinvestment Rate [float]:", false);
  sscanf(strBuf.c_str()," %lf \n", &Settings::Interest_Reinvestment_Rate);


  strBuf = IO::read_line_after(File, "Quarters Between Rebalancing [int]:", false);
  sscanf(strBuf.c_str()," %d \n", &Settings::Quarters_Between_Rebalancing);



  //////////////////////////////////////////////////////////////////////////////
  // Data Settings

  char Buf[256];

  strBuf = IO::read_line_after(File, "Past Stock Returns File [string]:", false);
  sscanf(strBuf.c_str(), " %s \n", Buf);
  Settings::Past_Stock_Returns_File = std::string{Buf};

  strBuf = IO::read_line_after(File, "Past Bond Returns File [string]:", false);
  sscanf(strBuf.c_str(), " %s \n", Buf);
  Settings::Past_Bond_Returns_File = std::string{Buf};



  // All done. Close the settings file!
  File.close();
} // void Settings::Parser::Read(void) {
