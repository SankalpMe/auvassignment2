#include <yaml-cpp/yaml.h>
#include <iostream>
int main(int argc, char const *argv[])
{
    YAML::Node config = YAML::LoadFile("temp.yaml");

    if (config["NAME"]) {
      std::cout << config["NAME"] << "\n";
    }
    return 0;
}
