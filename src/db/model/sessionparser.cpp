#include "db/model/sessionparser.hpp"

DTOSessionParser::DTOSessionParser(const Session &session)
{
    sessionDTO.id = session.getId();
    sessionDTO.startTime = clock_spec::to_time_t(session.getStartTime());
    sessionDTO.endTime = clock_spec::to_time_t(session.getEndTime());

    for (auto snapshot : session)
        decomposeSnapshot(snapshot);
}

SessionDTO DTOSessionParser::getSessionDTO() const
{
    return sessionDTO;
}

std::list<DBSnapshot> DTOSessionParser::getSnapshotDTOs() const
{
    return snapshotDTOs;
}

void DTOSessionParser::decomposeSnapshot(const Snapshot &snapshot)
{
    DBSnapshot snapshotDTO;

    snapshotDTO.sessionId = sessionDTO.id;
    decomposeCard(snapshotDTO, snapshot.getCard());
    snapshotDTO.param = snapshot.getParamType();
    snapshotDTO.knowledgeDegree = snapshot.getKnowledgeDegree();
    snapshotDTO.timePoint = clock_spec::to_time_t(snapshot.getTimePoint());

    snapshotDTOs.push_back(snapshotDTO);
}

void DTOSessionParser::decomposeCard(DBSnapshot &dst, const Card &card)
{
    dst.cardId = card.getId();
    dst.cardSymbol = card.getSymbol();
    dst.cardReading = card.getReading();
    dst.cardDescription = card.getDescription();
}
