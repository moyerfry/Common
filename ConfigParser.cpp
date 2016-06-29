#include "ConfigParser.h"
#include <cstdio>
#include <algorithm>

#define DEFAULT_SEPERATOR "="
#define DEFAULT_CONFIG_SEPERATOR ""

ConfigParser::ConfigParser()
{
  this->initialized = false;
}

ConfigParser::ConfigParser(std::string file_name):ConfigParser(file_name, DEFAULT_SEPERATOR)
{
}

ConfigParser::ConfigParser(std::string file_name, std::string delimiter) :
  ConfigParser(file_name, delimiter, DEFAULT_CONFIG_SEPERATOR)
{
}

ConfigParser::ConfigParser(std::string file_name, std::string delimiter, std::string new_config)
{
  this->initialized = false;
  this->parse(file_name, delimiter, new_config);
}

void ConfigParser::parse(std::string file_name, std::string delimiter, std::string config_seperator)
{
  printf("Parsing %s\n", file_name.c_str());
  std::ifstream config_file;
  config_file.open(file_name.c_str());

  if(!config_file.is_open())
  {
    printf("Failed to open %s\n", file_name.c_str());
    printf("Code will be run using only default options\n");
    return;
  }

  std::string line;
  dictionary new_config;
  while(getline(config_file, line))
  {
    int index = line.find(delimiter.c_str());
    if(index >= 0)
    {
      int start = 0;
      while((int) line[start] < (int) '!')
      {
        start++;
      }
      std::string key = line.substr(start, index - start);
      std::string value = line.substr(index + delimiter.size());
      new_config[key] = value;
    }
    else if((config_seperator.compare(DEFAULT_CONFIG_SEPERATOR) == 0 || config_seperator.compare(line) == 0) &&
              new_config.size() > 0)
    {
      configs.push_back(new_config);
      new_config.clear();
    }
  }

  if(new_config.size() > 0)
  {
    configs.push_back(new_config);
  }

  active_dict = 0;
  this->initialized = true;
}

std::string ConfigParser::get(std::string key, std::string def)
{
  if(this->hasKey(key))
  {
    return configs[active_dict][key];
  }
  else if(!initialized);
  {
    printf("Key %s not found in your config file\n", key.c_str());
    return def;
  }
}

int ConfigParser::get(std::string key, int def)
{
  std::string param = this->get(key, (std::string) "");
  if(param.compare("") == 0)
  {
    // The get method will have already yelled at them
    return def;
  }
  else
  {
    return std::stoi(param);
  }
}

double ConfigParser::get(std::string key, double def)
{
  std::string param = this->get(key, (std::string) "");
  if(param.compare("") == 0)
  {
    // The get method will have already yelled at them
    return def;
  }
  else
  {
    return std::stod(param);
  }
}

bool ConfigParser::get(std::string key, bool def)
{
  std::string param = this->get(key, (std::string) "");
  std::transform(param.begin(), param.end(), param.begin(), ::tolower);
  if(param.compare("") == 0)
  {
    // The get method will have already yelled at them
    return def;
  }
  else
  {
    return param.compare("true") == 0;
  }
}
