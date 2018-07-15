#include "./include/ACBExtractor.h"

ACBExtractor::ACBExtractor(std::string acbFile) {
  path = acbFile;
  headerTable = new UTFTable(acbFile);
  tracklist = new TrackList(headerTable);

  acbData* awbData = headerTable->get(0, "AwbFile");
  unsigned char* awbbuf = new unsigned char[awbData->length];
  headerTable->readBinary(awbbuf, static_cast<unsigned int*>(awbData->data)[0], static_cast<unsigned int*>(awbData->data)[1]);
  awbFile = new AFSArchive(awbbuf, awbData->length);
  delete[] awbbuf;
}

bool ACBExtractor::extract() {
  std::experimental::filesystem::path p;
  if (!path.is_absolute()) p = std::experimental::filesystem::canonical(path);
  else p = path;
  std::experimental::filesystem::path targetDir = p.replace_filename(std::experimental::filesystem::path("_acb_") += p.filename());
  std::experimental::filesystem::create_directories(targetDir);

  std::ofstream fs;
  for (unsigned int i = 0; i < tracklist->length; i++) {
    int inFiles = -1;
    for (unsigned int j = 0; j < awbFile->header->fileCount; j++) {
      if (tracklist->tracks[i].wavId == awbFile->files[j].id) {
        inFiles = j;
        break;
      }
    }
    if (inFiles != -1) {
      std::string cueName = tracklist->tracks[i].cueName;
      std::string encodeType = "";
      switch (tracklist->tracks[i].encodeType) {
      case 0: {
        encodeType = ".adx";
        break;
      }
      case 2: {
        encodeType = ".hca";
        break;
      }
      case 7: {
        encodeType = ".at3";
        break;
      }
      case 8: {
        encodeType = ".vag";
        break;
      }
      case 9: {
        encodeType = ".bcwav";
        break;
      }
      case 13: {
        encodeType = ".dsp";
        break;
      }
      default:
        break;
      }
      std::experimental::filesystem::path filename = targetDir;
      fs.open(filename.append(cueName + encodeType), std::ios::binary);
      fs.write((const char*)awbFile->files[inFiles].buf, awbFile->files[inFiles].length);
      fs.close();
    }
    else {
      return false; 
    }
  }
  return true;
}

ACBExtractor::~ACBExtractor() {
  delete headerTable;
  delete tracklist;
  delete awbFile;
}
