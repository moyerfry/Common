#include "ConfigParser.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>

void test(bool val, std::string text)
{
  static int num = 1;
  if(!val) printf("\n");
  printf("Test %i: %s: %s\n", num, text.c_str(), (val ? "pass" : "fail"));
  if(!val) printf("\n");
  num++;
}

int main()
{
  ConfigParser test_config_parser("test_config_file.txt");
  ConfigParser non_default_config_parser("test_config_file_not_defaults.txt", "pasta", "gobbledegook");

  test(non_default_config_parser.getNumDicts() == 2, "Number of active dicts");

  non_default_config_parser.setActiveDict(1);
  test(non_default_config_parser.get("c", 0.0) == 4.6, "Get float");
  test(non_default_config_parser.get("d", true) == false, "Get bool");
  test(test_config_parser.get("d", false) == true, "Get bool ignore case");
  test(non_default_config_parser.get("a", 0) == 5, "Get int");

  return 0;
}
