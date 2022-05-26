#include "dto/sessionbuilder.hpp"

DTOSessionBuilder::DTOSessionBuilder(const SessionDTO &sessionDTO)
    : sessionDTO(sessionDTO)
{
}

void DTOSessionBuilder::addSnapshotDTO(const SnapshotDTO &snapshotDTO)
{
    snapshotDTOs.push_back(snapshotDTO);
}

Session DTOSessionBuilder::build()
{
    Session session(sessionDTO.id,
                    std::chrono::system_clock::from_time_t(sessionDTO.startTime),
                    std::chrono::system_clock::from_time_t(sessionDTO.endTime));

    for (auto snapshotDTO : snapshotDTOs)
        session.addSnapshot(buildSnapshot(snapshotDTO));

    return session;
}

Snapshot DTOSessionBuilder::buildSnapshot(const SnapshotDTO &snapshotDTO)
{
    /// QUESTION: where to get card?
    /// TODO: get card somewhere
    Snapshot snapshot(
        Card(snapshotDTO.cardId),
        snapshotDTO.param == 0 ? Snapshot::ParamType::READING : Snapshot::ParamType::TRANSLATION,
        snapshotDTO.knowledgeDegree,
        std::chrono::system_clock::from_time_t(snapshotDTO.timePoint));

    return snapshot;
}
