#pragma once

#include <string>
#include <map>
#include "solution.hpp"

class ConfigFileSolution : public Solution
{
public:
    ConfigFileSolution(const std::string &filename);

private:
    void loadCollectionRepoConfig();
    void loadSessionRepoConfig();

    void loadLearnerConfig();
    void loadEstimatorConfig();

    void loadUIFactoryConfig();

    void loadOptions(const std::string &filename);

    std::map<std::string, std::string> options;
};
