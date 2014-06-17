#ifndef LADIA_TABLELOGGER_H
#define LADIA_TABLELOGGER_H

#include <string>
#include <vector>
#include <iostream>

class TableLogger 
{
public:
  enum Justification {
    kLeft,
    kRight,
    kCenter
  };

  // column header, justification
  typedef std::pair<std::string, Justification> HeaderStyle;

  // initialize with title and header
  TableLogger(const std::string&, const std::vector<HeaderStyle> &);

  void LogTableHead();
  void LogTableRow(std::vector<std::string> data);

private:
  std::string title_;
  std::vector<HeaderStyle> header_;
  std::string header_space_;

  void LogJustifiedData(const std::string &, HeaderStyle);

  // Returns a new string of length n, containing the given string centered
  // surrounded on either side with an equal number of spaces
  // If the given string does not fit in the given length, it is truncated to fit
  std::string Center(const std::string &s, std::string::size_type length);
};

#endif
