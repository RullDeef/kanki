#include "db/model/sessionbuilder.hpp"

DTOSessionBuilder::DTOSessionBuilder(const SessionDTO &sessionDTO)
    : sessionDTO(sessionDTO)
{
}

void DTOSessionBuilder::addSnapshotDTO(const DBSnapshot &snapshotDTO)
{
    snapshotDTOs.push_back(snapshotDTO);
}

Session DTOSessionBuilder::build()
{
    Session session(sessionDTO.id,
                    clock_spec::from_time_t(sessionDTO.startTime),
                    clock_spec::from_time_t(sessionDTO.endTime));

    for (auto snapshotDTO : snapshotDTOs)
        session.addSnapshot(buildSnapshot(snapshotDTO));

    return session;
}

Snapshot DTOSessionBuilder::buildSnapshot(const DBSnapshot &snapshotDTO)
{
    Card card(snapshotDTO.cardId,
              snapshotDTO.cardSymbol,
              snapshotDTO.cardReading,
              snapshotDTO.cardDescription);

    Snapshot snapshot(
        card,
        Snapshot::ParamType(snapshotDTO.param),
        snapshotDTO.knowledgeDegree,
        clock_spec::from_time_t(snapshotDTO.timePoint));

    return snapshot;
}
