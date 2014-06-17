#include "tablelogger.h"
#include <cassert>
#include <iomanip>

TableLogger::TableLogger(
  const std::string& title, const std::vector<HeaderStyle> &header)
  :title_(title), header_(header), header_space_(3, ' ')
{}

void TableLogger::LogTableHead()
{
  using std::cout;

  cout << title_ << "\n";

  std::vector<HeaderStyle>::iterator h; 
  for(h = header_.begin(); h != header_.end(); ++h) {
    cout << h->first << header_space_;
  }
  cout << "\n";
}

void TableLogger::LogTableRow(std::vector<std::string> data)
{
  assert(("Row data does not align with available columns.", 
    data.size() == header_.size()));

  using std::cout;
  for(std::size_t i = 0; i < data.size(); ++i) {
    LogJustifiedData(data[i], header_[i]);
    cout << header_space_;
  }
  cout << "\n";
}

std::string TableLogger::Center(const std::string &s, std::string::size_type length) 
{
  if(s.length() > length) 
    return s.substr(0, length);

  std::string result(length, ' ');
  int spaces = (length - s.length()) / 2;

  for(unsigned int i = 0; i < s.length(); ++i)
    result[i+spaces] = s[i];
  return result;
}

void TableLogger::LogJustifiedData(const std::string &s, HeaderStyle style)
{
  using std::cout;
  Justification just = style.second;
  int columnwidth = style.first.length();

  if(just == kCenter)
    cout << Center(s, columnwidth);
  else if(just == kRight)
    cout << std::right << std::setw(columnwidth) << s;
  else // default to left justify
    cout << std::left << std::setw(columnwidth) << s;

}
