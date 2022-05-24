#pragma once

#include <string>
#include <fstream>
#include "tools/logger.hpp"
#include "tools/idgenerator.hpp"
#include "core/icollectionrepository.hpp"

class FileCollectionRepository : public ICollectionRepository
{
public:
    FileCollectionRepository(const std::string& filename)
        : filename(filename)
    {
        try { load(); }
        catch (const std::exception& e) {
            ERROR_METHOD(e.what());
        }
    }

    ~FileCollectionRepository() {
        try { dump(); }
        catch (const std::exception& e) {
            ERROR_METHOD(e.what());
        }
    }

    // loads data from disk
    void load() {
        ///TODO: implement correctly
        std::wifstream file(filename);

        if (!file)
            throw std::runtime_error("bad filename");

        IdGenerator idGenerator;
        Collection collection(idGenerator());

        do {
            std::wstring deckName;
            std::getline(file, deckName);

            size_t deckSize;
            file >> deckSize >> std::ws;

            Deck deck(idGenerator(), deckName);
            for (size_t i = 0; i < deckSize; i++) {
                std::wstring symbol, reading, description;
                std::getline(file, symbol);
                std::getline(file, reading);
                std::getline(file, description);

                deck.addCard(Card(idGenerator(), symbol, reading, description));
            }
            file >> std::ws;
            collection.addDeck(std::move(deck));
        } while (!file.eof());

        collections = { collection };
    }

    // writes data on disk
    void dump() {
        ///TODO: implement correctly
        std::wofstream file(filename);

        if (!file)
            throw std::runtime_error("bad filename");

        for (const auto& deck : collections.front())
        {
            file << deck.getName() << std::endl;
            file << deck.size() << std::endl;

            for (const auto& card : deck)
            {
                file << card.getSymbol() << std::endl;
                file << card.getReading() << std::endl;
                file << card.getDescription() << std::endl;
            }
        }
    }

    virtual std::list<Collection> getCollections() override {
        return collections;
    }

    virtual Collection getCollectionById(size_t id) override {
        LOG_METHOD();

        auto iter = std::find_if(collections.begin(), collections.end(),
            [id](const Collection& collection) { return collection.getId() == id; });
        
        if (iter == collections.end())
            throw std::runtime_error("bad collection id");
        return *iter;
    }

    virtual void removeCollection(size_t id) override {
        LOG_METHOD();

        collections.erase(
            std::remove_if(collections.begin(), collections.end(),
                [id](const Collection& collection) { return collection.getId() == id; }),
            collections.end());
    }

    virtual void saveCollection(const Collection& collection) override {
        LOG_METHOD();

        size_t id = collection.getId();
        auto iter = std::find_if(collections.begin(), collections.end(),
            [id](const Collection& collection) { return collection.getId() == id; });
        
        if (iter != collections.end())
            *iter = collection;
        else
            collections.push_back(collection);
    }

private:
    std::string filename;
    std::list<Collection> collections;
};
