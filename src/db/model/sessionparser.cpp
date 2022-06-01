#include "db/model/sessionparser.hpp"

DBSessionParser::DBSessionParser(const Session &session)
{
    dbSession.id = session.getId();
    dbSession.startTime = clock_spec::to_time_t(session.getStartTime());
    dbSession.endTime = clock_spec::to_time_t(session.getEndTime());

    for (auto snapshot : session)
        decomposeSnapshot(snapshot);
}

DBSession DBSessionParser::getSession() const
{
    return dbSession;
}

std::list<DBSnapshot> DBSessionParser::getSnapshots() const
{
    return dbSnapshots;
}

void DBSessionParser::decomposeSnapshot(const Snapshot &snapshot)
{
    DBSnapshot snapshotDTO;

    snapshotDTO.sessionId = dbSession.id;
    decomposeCard(snapshotDTO, snapshot.getCard());
    snapshotDTO.param = snapshot.getParamType();
    snapshotDTO.knowledgeDegree = snapshot.getKnowledgeDegree();
    snapshotDTO.timePoint = clock_spec::to_time_t(snapshot.getTimePoint());

    dbSnapshots.push_back(snapshotDTO);
}

void DBSessionParser::decomposeCard(DBSnapshot &dst, const Card &card)
{
    dst.cardId = card.getId();
    dst.cardSymbol = card.getSymbol();
    dst.cardReading = card.getReading();
    dst.cardDescription = card.getDescription();
}
