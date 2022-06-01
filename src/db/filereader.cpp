#include <iostream>
#include "tools/uuid.hpp"
#include "db/filereader.hpp"

FileReader::FileReader(const std::string &filename)
    : stream(filename)
{
    if (!stream)
        throw std::runtime_error("bad file for reader");
}

DBCard FileReader::readCardDTO()
{
    DBCard card;

    stream >> card.id >> std::ws;
    stream >> card.deckId >> std::ws;
    std::getline(stream, card.symbol);
    std::getline(stream, card.reading);
    std::getline(stream, card.description);

    return card;
}

DBDeck FileReader::readDeckDTO()
{
    DBDeck deck;

    stream >> deck.id >> std::ws;
    stream >> deck.collectionId >> std::ws;
    std::getline(stream, deck.name);

    return deck;
}

DBDeckCollection FileReader::readCollectionDTO()
{
    DBDeckCollection collection;

    stream >> collection.id >> std::ws;
    std::getline(stream, collection.name);

    return collection;
}

DBSnapshot FileReader::readSnapshotDTO()
{
    DBSnapshot snapshot;

    stream >> snapshot.sessionId >> std::ws;
    stream >> snapshot.cardId >> std::ws;
    std::getline(stream, snapshot.cardSymbol);
    std::getline(stream, snapshot.cardReading);
    std::getline(stream, snapshot.cardDescription);
    stream >> snapshot.param >> std::ws;
    stream >> snapshot.knowledgeDegree >> std::ws;
    stream >> snapshot.timePoint >> std::ws;

    return snapshot;
}

DBSession FileReader::readSessionDTO()
{
    DBSession session;

    stream >> session.id >> std::ws;
    stream >> session.startTime >> std::ws;
    stream >> session.endTime >> std::ws;

    return session;
}

size_t FileReader::readCount()
{
    size_t count;

    stream >> count >> std::ws;

    return count;
}
