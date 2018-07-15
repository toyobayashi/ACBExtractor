#include <iostream>
#include "./include/ACBExtractor.h"

using namespace std;

int main(int argc, char** argv) {
  ACBExtractor* acb;
  try {
    for (int x = 1; x < argc; x++) {
      acb = new ACBExtractor(argv[x]);

      if (acb->extract()) {
        for (unsigned int i = 0; i < acb->tracklist->length; i++) {
          cout << acb->tracklist->tracks[i].cueName.c_str() << endl;
        }
      }
      delete acb;
    }
  } catch (const char* err) {
    cout << err << endl;
    return 0;
  }

  return 0;
}
