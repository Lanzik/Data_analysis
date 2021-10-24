#include <iostream>
#include "Goodreads.hpp"
#include "definition.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  Goodreads goodreads(argv[FILES_FOLDER]);
  string command;
  while(getline(cin, command))
  {
    goodreads.read_command(command);
  }
}
