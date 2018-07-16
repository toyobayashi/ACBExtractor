#pragma once
#include "./Reader.h"

typedef struct {
  std::string columnName;
  void* data;
  unsigned char dataType;
  unsigned int length;
} acbData;

typedef struct {
  unsigned char columnType;
  std::string columnName;
  void* data;
  unsigned char dataType;
  unsigned int length;
} acbColumn;

typedef acbData* acbRow;

typedef struct {
  unsigned short u1;
  unsigned short tableDataOffset;
  unsigned int stringDataOffset;
  unsigned int binaryDataOffset;
  unsigned int tableNameStringOffset;
  unsigned short columnLength;
  unsigned short rowTotalByte;
  unsigned int rowLength;
} acbHeader;

class UTFTable {
private:
  typedef struct {
    const unsigned char ZERO;
    const unsigned char CONSTANT;
    const unsigned char PERROW;
    const unsigned char CONSTANT2;
  } acbColumnType;
  
  static unsigned int dataLength[12];
  static acbColumnType columnType;
  Reader* r;
  void readHeader();
  std::string readString(std::streampos offset);
  void readBinary(unsigned char* outbuf, std::streampos offset, std::streampos length);
  void readColumns();
  void readRows();
  template<typename Arg>
  void readData(unsigned char type, Arg& columnOrData);
  template<typename T, typename Arg>
  void readDataTemplate(Arg& columnOrData);
  template<typename Arg>
  void deleteVoid(Arg& columnOrData);
public:
  friend class TrackList;
  friend class ACBExtractor;

  unsigned int length;
  acbHeader* header;
  acbColumn* columns;
  acbRow* rows;
  
  std::string name;
  UTFTable(std::string acb);
  UTFTable(unsigned char* acb, unsigned int l);
  ~UTFTable();
  acbData* get(unsigned int lineNumber, std::string columnName);
};
