#pragma once

#include <list>
#include "model/snapshot.hpp"
#include "model/session.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class DTOSessionParser
{
public:
    DTOSessionParser(const Session &session);

    SessionDTO getSessionDTO() const;
    std::list<DBSnapshot> getSnapshotDTOs() const;

private:
    void decomposeSnapshot(const Snapshot &snapshot);
    void decomposeCard(DBSnapshot &dst, const Card &card);

    SessionDTO sessionDTO;
    std::list<DBSnapshot> snapshotDTOs;
};
