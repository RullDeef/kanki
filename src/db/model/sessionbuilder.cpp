#include "db/model/sessionbuilder.hpp"

DBSessionBuilder::DBSessionBuilder(const DBSession &dbSession)
    : dbSession(dbSession)
{
}

void DBSessionBuilder::addSnapshotDTO(const DBSnapshot &snapshotDTO)
{
    dbSnapshots.push_back(snapshotDTO);
}

Session DBSessionBuilder::build()
{
    Session session(dbSession.id,
                    clock_spec::from_time_t(dbSession.startTime),
                    clock_spec::from_time_t(dbSession.endTime));

    for (auto snapshotDTO : dbSnapshots)
        session.addSnapshot(buildSnapshot(snapshotDTO));

    return session;
}

Snapshot DBSessionBuilder::buildSnapshot(const DBSnapshot &snapshotDTO)
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
