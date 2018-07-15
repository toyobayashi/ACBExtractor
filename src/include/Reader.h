#pragma once
# include <fstream>

class Reader : public std::ifstream {
private:
  
  static int isLittleEndian;
  void checkEndian();
  std::string tmpfile = "";

public:
  unsigned int length;
  Reader(unsigned char* buf, unsigned int length);
  Reader();
  ~Reader();
  Reader(std::string filename, ios_base::openmode mode);
  void open(std::string filename, ios_base::openmode mode);
  std::streampos tell();
  Reader& seek(std::streampos at, std::streampos offset = 0);
  unsigned int readUInt32BE();
  unsigned int readUInt32LE();
  unsigned long long readUInt64BE();
  unsigned long long readUInt64LE();
  unsigned short readUInt16BE();
  unsigned short readUInt16LE();
  unsigned char readUInt8();
  char readInt8();
  short readInt16BE();
  short readInt16LE();
  int readInt32BE();
  int readInt32LE();
  long long readInt64BE();
  long long readInt64LE();
  double readDoubleBE();
  double readDoubleLE();
  float readFloatBE();
  float readFloatLE();
  unsigned int readUIntLE(unsigned int size);

  template<typename T>
  T readByte(bool isLE = false);
};
