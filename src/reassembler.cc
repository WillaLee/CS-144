#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  const uint64_t index = first_index - first_index_;
  if (index + data.size() <= this->writer().available_capacity()) {
    insert(index, data);
  }
  if (first_index == first_index_) {
    string output;
    while (unassembled_data[0] != '\0')
    {
      output += unassembled_data[0];
      unassembled_data.pop_front();
    }
    this->writer().push(output);
    first_index_ += output.size();
    bytes_pending_ -= output.size();
  }
  if ( is_last_substring )
    this->writer().close();
}

uint64_t Reassembler::bytes_pending() const
{
  return bytes_pending_;
}

void Reassembler::insert( const uint64_t index, std::string data )
{
  std::deque<char>::iterator i;
  while (index > unassembled_data.size()) {
    unassembled_data.push_back('\0');
  }
  i = unassembled_data.begin() + index;
  for (char c : data) {
    if (i == unassembled_data.end())
    {
      unassembled_data.push_back(c);
      bytes_pending_++;
    }
    else if (*i != '\0')
    {
      *i = c;
      bytes_pending_++;
    }
  }
}
