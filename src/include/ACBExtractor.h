#pragma once
#include "./UTFTable.h"
#include "./AFSArchive.h"
#include "./TrackList.h"
// #include <experimental/filesystem>

class ACBExtractor {
private:

public:
  std::string path;
  UTFTable* headerTable;
  TrackList* tracklist;
  AFSArchive* awbFile;

  ACBExtractor(std::string acbFile);

  bool extract();

  ~ACBExtractor();
};