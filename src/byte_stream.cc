#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  return is_closed_;
}

void Writer::push( string data )
{
  uint64_t len = data.length(),
           cap = available_capacity();
  if (len > cap) {
    data = data.substr(0, cap);
    len = cap;
  }
  for (uint64_t i = 0; i < len; i++) {
    data_.push_back(data[i]);
  }
  bytes_pushed_ += len;
}

void Writer::close()
{
  is_closed_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - data_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

bool Reader::is_finished() const
{
  if ( bytes_buffered() == 0 && is_closed_)
    return true;
  return false;
}

uint64_t Reader::bytes_popped() const
{
  return bytes_popped_;
}

string_view Reader::peek() const
{
  if (bytes_buffered() == 0) {
    return string_view{};
  }
  return {&data_[0], 1};
}

void Reader::pop( uint64_t len )
{
  if (len > bytes_buffered()) {
    len = bytes_buffered();
  }
  bytes_popped_ += len;
  for (uint64_t i = 0; i < len; i++) {
    data_.pop_front();
  }
}

uint64_t Reader::bytes_buffered() const
{
  return data_.size();
}
