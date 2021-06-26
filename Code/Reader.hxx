#ifndef READER_HXX
#define READER_HXX

#include "Returns.hxx"

namespace Reader {

// Prototypes.
std::vector<Returns::Quarterly> Read_Past_Returns(const char * File_Path);

} // namespace Reader {

#endif
