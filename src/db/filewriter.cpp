#include "db/filewriter.hpp"

FileWriter::FileWriter(const std::string &filename)
    : stream(filename)
{
    if (!stream)
        throw std::runtime_error("bad file for writer");
}

void FileWriter::writeCardDTO(const CardDTO &card)
{
    stream << card.id << std::endl;
    stream << card.deckId << std::endl;
    stream << card.symbol << std::endl;
    stream << card.reading << std::endl;

    /// WARNING: only oneline description supported
    stream << card.description << std::endl;
}

void FileWriter::writeDeckDTO(const DeckDTO &deck)
{
    stream << deck.id << std::endl;
    stream << deck.collectionId << std::endl;
    stream << deck.name << std::endl;
}

void FileWriter::writeCollectionDTO(const CollectionDTO &collection)
{
    stream << collection.id << std::endl;
    stream << collection.name << std::endl;
}

void FileWriter::writeSnapshotDTO(const SnapshotDTO &snapshot)
{
    stream << snapshot.sessionId << std::endl;
    stream << snapshot.cardId << std::endl;
    stream << snapshot.param << std::endl;
    stream << snapshot.knowledgeDegree << std::endl;
    stream << snapshot.timePoint << std::endl;
}

void FileWriter::writeSessionDTO(const SessionDTO &session)
{
    stream << session.id << std::endl;
    stream << session.startTime << std::endl;
    stream << session.endTime << std::endl;
}

void FileWriter::writeCount(size_t count)
{
    stream << count << std::endl;
}
