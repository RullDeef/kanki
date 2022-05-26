#include "dto/sessionparser.hpp"

DTOSessionParser::DTOSessionParser(const Session &session)
{
    sessionDTO.id = session.getId();
    sessionDTO.startTime = std::chrono::system_clock::to_time_t(session.getStartTime());
    sessionDTO.endTime = std::chrono::system_clock::to_time_t(session.getEndTime());

    for (auto snapshot : session)
        decomposeSnapshot(snapshot);
}

SessionDTO DTOSessionParser::getSessionDTO() const
{
    return sessionDTO;
}

std::list<SnapshotDTO> DTOSessionParser::getSnapshotDTOs() const
{
    return snapshotDTOs;
}

void DTOSessionParser::decomposeSnapshot(const Snapshot &snapshot)
{
    SnapshotDTO snapshotDTO;

    snapshotDTO.sessionId = sessionDTO.id;
    snapshotDTO.cardId = snapshot.getCard().getId();
    snapshotDTO.param = snapshot.getParamType() == Snapshot::ParamType::READING ? 0 : 1;
    snapshotDTO.knowledgeDegree = snapshot.getKnowledgeDegree();
    snapshotDTO.timePoint = std::chrono::system_clock::to_time_t(snapshot.getTimePoint());

    snapshotDTOs.push_back(snapshotDTO);
}
