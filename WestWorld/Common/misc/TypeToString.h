#ifndef TYPE_TO_STRING_H
#define TYPE_TO_STRING_H
//-----------------------------------------------------------------------------
//  Desc:   an interface for a class that has a static
//          method for converting an int into a string. (useful when debugging
//          to convert enumerations)
//-----------------------------------------------------------------------------
#include <string>

class TypeToString
{
public:

  virtual std::string Convert(int enumeration)=0;
};

#endif