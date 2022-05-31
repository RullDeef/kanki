#pragma once

#include <list>
#include "model/session.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class DBSessionBuilder
{
public:
    DBSessionBuilder(const DBSession& dbSession);

    void addSnapshotDTO(const DBSnapshot& snapshotDTO);

    Session build();

private:
    Snapshot buildSnapshot(const DBSnapshot& snapshotDTO);

    DBSession dbSession;
    std::list<DBSnapshot> dbSnapshots;
};
