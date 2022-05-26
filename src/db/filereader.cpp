#include <iostream>
#include "db/filereader.hpp"

FileReader::FileReader(std::wifstream &stream)
    : stream(stream)
{
    if (!stream)
        throw std::runtime_error("bad file for reader");
}

CardDTO FileReader::readCardDTO()
{
    CardDTO card;

    stream >> card.id >> std::ws;
    stream >> card.deckId >> std::ws;
    std::getline(stream, card.symbol);
    std::getline(stream, card.reading);
    std::getline(stream, card.description);

    return card;
}

DeckDTO FileReader::readDeckDTO()
{
    DeckDTO deck;

    stream >> deck.id >> std::ws;
    stream >> deck.collectionId >> std::ws;
    std::getline(stream, deck.name);

    return deck;
}

CollectionDTO FileReader::readCollectionDTO()
{
    CollectionDTO collection;

    stream >> collection.id >> std::ws;
    std::getline(stream, collection.name);

    return collection;
}

SnapshotDTO FileReader::readSnapshotDTO()
{
    SnapshotDTO snapshot;

    stream >> snapshot.sessionId >> std::ws;
    stream >> snapshot.cardId >> std::ws;
    stream >> snapshot.param >> std::ws;
    stream >> snapshot.knowledgeDegree >> std::ws;
    stream >> snapshot.timePoint >> std::ws;

    return snapshot;
}

SessionDTO FileReader::readSessionDTO()
{
    SessionDTO session;

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
