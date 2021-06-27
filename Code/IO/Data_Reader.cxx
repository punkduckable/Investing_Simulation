#include <cstdio>
#include <cstring>
#include <vector>

#include "Data_Reader.hxx"



std::vector<Returns::Quarterly> Reader::Read_Past_Returns(const char * File_Path) {
  /* This function reads past returns from a csv file. The csv should have a
  header line followed by one or more lines that have the following form:
        <capital gains>,<current income>
  Where <capital gains> specifies the rate of return (as a percentage) for one
  quarter. This should be the % that the stock/bond/index's price rose in that
  quarter. The <current income> should specify how much current income
  (either dividends for stocks or interest for bonds) the stock/bond/index paid
  out in that quarter as a percentage of the price of the stock/bond/index at
  the end of that quarter.

  For example, suppose that some stock paid out $2 in  dividends at the end of
  the 3rd quarter of some year. When they paid out the diviend, the stock was
  trading for $50/share. Thus, the $2 dividend was worth 4% of the stock's value
  In this case, what we call <curent income> would be .04. */

  // Open the file!
  FILE* File = std::fopen(File_Path, "r");

  // Initialize some buffers. We'll use these a few times.
  const unsigned Buffer_Length = 256;
  char Buffer[Buffer_Length];

  // Now, figure out how many lines are in this file.
  unsigned Num_Lines = 0;
  while(true) {
    if(std::fgets(Buffer, Buffer_Length, File) == NULL) { break; }
    else { Num_Lines++; }
  } // while(true) {

  // Reset the file pointer to the start of the file.
  std::fseek(File, 0, SEEK_SET);

  // Initialize an array of Price_Lines. This will hold the opening prices
  // for each line in the file. Note that we initialize it to have Num_Lines - 1
  // elements, since the first line is a header.
  std::vector<Returns::Quarterly> Past_Returns(Num_Lines - 1);

  // Read the header line/toss it.
  std::fgets(Buffer, Buffer_Length, File);

  // Read the Lines, one at a time.
  for(unsigned i = 0; i < Num_Lines - 1; i++) {
    // Read the next line (which should exist... assuming we read the number
    // of lines correctly)
    std::fgets(Buffer, Buffer_Length, File);

    // Read Dividends, Capital Gains.
    std::sscanf( Buffer,
                "%lf,%lf\n",
                &(Past_Returns[i]).Capital_Gains,
                &(Past_Returns[i]).Current_Income);
  } // for(int i = 0; i < Num_Lines - 1; i++) {

  // All done! Close the file.
  std::fclose(File);

  return Past_Returns;
} // std::vector<Returns::Quarterly> Reader::Read_Past_Returns(const char * File_Path) {
