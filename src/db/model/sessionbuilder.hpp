#pragma once

#include <list>
#include "model/session.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class DTOSessionBuilder
{
public:
    DTOSessionBuilder(const SessionDTO& sessionDTO);

    void addSnapshotDTO(const DBSnapshot& snapshotDTO);

    Session build();

private:
    Snapshot buildSnapshot(const DBSnapshot& snapshotDTO);

    SessionDTO sessionDTO;
    std::list<DBSnapshot> snapshotDTOs;
};
