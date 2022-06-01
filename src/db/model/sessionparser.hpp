#pragma once

#include <list>
#include "model/snapshot.hpp"
#include "model/session.hpp"
#include "db/model/snapshot.hpp"
#include "db/model/session.hpp"

class DBSessionParser
{
public:
    DBSessionParser(const Session &session);

    DBSession getSession() const;
    std::list<DBSnapshot> getSnapshots() const;

private:
    void decomposeSnapshot(const Snapshot &snapshot);
    void decomposeCard(DBSnapshot &dst, const Card &card);

    DBSession dbSession;
    std::list<DBSnapshot> dbSnapshots;
};
