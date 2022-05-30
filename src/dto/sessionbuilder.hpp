#pragma once

#include <list>
#include "model/session.hpp"
#include "dto/snapshot.hpp"
#include "dto/session.hpp"

class DTOSessionBuilder
{
public:
    DTOSessionBuilder(const SessionDTO& sessionDTO);

    void addSnapshotDTO(const SnapshotDTO& snapshotDTO);

    Session build();

private:
    Snapshot buildSnapshot(const SnapshotDTO& snapshotDTO);

    SessionDTO sessionDTO;
    std::list<SnapshotDTO> snapshotDTOs;
};
