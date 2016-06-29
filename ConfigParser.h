#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> dictionary;

class ConfigParser {
public:
  ConfigParser();
  ConfigParser(std::string file_name);
  ConfigParser(std::string file_name, std::string delimiter);
  ConfigParser(std::string file_name, std::string delimiter, std::string new_config);

  void parse(std::string file_name, std::string delimiter, std::string config_seperator);

  std::string get(std::string key, std::string def);
  int get(std::string key, int def);
  bool get(std::string key, bool def);
  double get(std::string key, double def);

  bool hasKey(std::string key) { return configs[active_dict][key].compare("") != 0; }

  void setActiveDict(int num) { active_dict = ((num < getNumDicts() && num >= 0) ? num : 0); }
  int getNumDicts() { return configs.size(); }

protected:

  std::vector<dictionary> configs;

  int active_dict;
  bool initialized;

};

#endif
