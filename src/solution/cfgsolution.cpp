#include <stdexcept>
#include <fstream>
#include "tools/logger.hpp"
#include "cfgsolution.hpp"

#include "core/spacedlearner.hpp"
#include "core/spacedestimator.hpp"

#include "db/filecollectionrepo.hpp"
#include "db/filesessionrepo.hpp"
#include "db/filedtoiofactory.hpp"

#include "db/fileimporter.hpp"
#include "db/fileexporter.hpp"

#include "ui/cli/uifactory.hpp"

#include "ui/qt/qtuifactory.hpp"

ConfigFileSolution::ConfigFileSolution(const std::string &filename)
{
    loadOptions(filename);

    loadCollectionRepoConfig();
    loadSessionRepoConfig();

    loadLearnerConfig();
    loadEstimatorConfig();
    loadUIFactoryConfig();

    registerImporter(std::shared_ptr<IImporter>(new FileImporter()));
    registerExporter(std::shared_ptr<IExporter>(new FileExporter()));

}

void ConfigFileSolution::loadCollectionRepoConfig()
{
    if (options.contains("collection"))
    {
        auto config = options["collection"];
        auto type = config.substr(0, config.find(':'));
        auto value = config.substr(config.find(':') + 1);

        if (type == "file")
        {
            auto ioFactory = std::shared_ptr<IDTOIOFactory>(
                new FileDTOIOFactory(value));
            auto repo = std::shared_ptr<ICollectionRepository>(
                new FileCollectionRepository(ioFactory));
            registerCollectionRepository(repo);
        }
        else
        {
            ERROR_METHOD("unknown type for collection repository");
            throw std::runtime_error("unknown type for collection repository");
        }
    }
    else
    {
        ERROR_METHOD("collection repository kind unknown");
        throw std::runtime_error("collection repository kind unknown");
    }
}

void ConfigFileSolution::loadSessionRepoConfig()
{
    if (options.contains("session"))
    {
        auto config = options["session"];
        auto type = config.substr(0, config.find(':'));
        auto value = config.substr(config.find(':') + 1);

        if (type == "file")
        {
            auto ioFactory = std::shared_ptr<IDTOIOFactory>(
                new FileDTOIOFactory(value));
            auto repo = std::shared_ptr<ISessionRepository>(
                new FileSessionRepository(ioFactory));
            registerSessionRepository(repo);
        }
        else
        {
            ERROR_METHOD("unknown type for session repository");
            throw std::runtime_error("unknown type for session repository");
        }
    }
    else
    {
        ERROR_METHOD("session repository kind unknown");
        throw std::runtime_error("session repository kind unknown");
    }
}

void ConfigFileSolution::loadLearnerConfig()
{
    /// TODO: implement
    registerLearner(std::shared_ptr<ILearner>(new SpacedLearner()));
}

void ConfigFileSolution::loadEstimatorConfig()
{
    /// TODO: implement
    registerEstimator(std::shared_ptr<IEstimator>(new SpacedEstimator()));
}

void ConfigFileSolution::loadUIFactoryConfig()
{
    if (options.contains("ui"))
    {
        auto value = options["ui"];

        if (value == "cli")
            registerUIFactory(std::shared_ptr<IUIFactory>(new cli::UIFactory()));
        else if (value == "qt")
            registerUIFactory(std::shared_ptr<IUIFactory>(new QtUIFactory()));
        else
        {
            ERROR_METHOD("unknown type for ui factory");
            throw std::runtime_error("unknown type for ui factory");
        }
    }
    else
    {
        ERROR_METHOD("ui factory kind unknown");
        throw std::runtime_error("ui factory kind unknown");
    }
}

void ConfigFileSolution::loadOptions(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        ERROR_METHOD("config file not found");
        throw std::runtime_error("config file not found");
    }

    while (true)
    {
        std::string line;
        std::getline(file, line);

        if (line.empty())
        {
            if (file.eof())
                break;
            else
                continue;
        }

        auto eqPos = line.find('=');
        auto key = line.substr(0, eqPos);
        auto value = line.substr(eqPos + 1);

        options.emplace(key, value);
    }
}
