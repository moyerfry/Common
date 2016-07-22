#include "ConfigParser.h"
#include "CircularBuffer.h"
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

void config_parser_tests()
{
  ConfigParser test_config_parser("test_config_file.txt");
  ConfigParser non_default_config_parser("test_config_file_not_defaults.txt", "pasta", "gobbledegook");

  non_default_config_parser.setActiveDict(1);
  test(non_default_config_parser.get("c", 0.0) == 4.6, "Get float");
  test(non_default_config_parser.get("d", true) == false, "Get bool");
  test(test_config_parser.get("d", false) == true, "Get bool ignore case");
  test(non_default_config_parser.get("a", 0) == 5, "Get int");
  test(non_default_config_parser.getNumDicts() == 2, "Number of active dicts");
}

void circular_buffer_tests()
{
  CircularBuffer<int> test_buffer(3);

  test_buffer.push(1);
  test_buffer.push(2);
  test_buffer.push(3);
  test_buffer.pop();
  test(test_buffer.pop() == 2, "Test buffer returned correct value");
  test_buffer.push(4);
  test_buffer.pop();
  test(test_buffer.pop() == 4, "Test buffer circled and returned the correct value");
}

int main()
{
  config_parser_tests();
  circular_buffer_tests();

  return 0;
}
