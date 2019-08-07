/**
 * Storage.cpp
 *
 * @date Aug 2, 2019
 * @author Irfan M
 */

#include <fstream>
#include <unistd.h>

#include "Storage.h"

namespace IrfanSec {

const string Storage::dataFile = "PassMgr.dat";

void Storage::remove() {
  unlink(dataFile.c_str()); // delete the file from disk
}

void Storage::write(const Users &users) {
  ofstream fout;
  fout.open(dataFile);

  if (!fout.is_open()) {
    return; // Could not open file
  }

  fout << users;

  fout.flush();
  fout.close();
}

Users Storage::read() {
  Users users;

  ifstream fin;
  fin.open(dataFile);

  if (!fin.is_open()) { // Check that we successfully opened the file
    return users;
  }

  fin >> users;

  fin.close();
  return users;
}

} /* namespace irfan */
