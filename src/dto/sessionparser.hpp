#pragma once

#include <list>
#include "model/snapshot.hpp"
#include "model/session.hpp"
#include "dto/snapshot.hpp"
#include "dto/session.hpp"

class DTOSessionParser
{
public:
    DTOSessionParser(const Session &session);

    SessionDTO getSessionDTO() const;
    std::list<SnapshotDTO> getSnapshotDTOs() const;

private:
    void decomposeSnapshot(const Snapshot &snapshot);
    void decomposeCard(SnapshotDTO &dst, const Card &card);

    SessionDTO sessionDTO;
    std::list<SnapshotDTO> snapshotDTOs;
};
