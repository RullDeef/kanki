#pragma once

#include <memory>
#include "model/cardsnapshot.hpp"
#include "model/session.hpp"
#include "snapshotinfo.hpp"
#include "sessioninfo.hpp"
#include "isessionrepo.hpp"

class SessionAdapter
{
public:
    explicit SessionAdapter(std::shared_ptr<ISessionRepository> repository);

    Session extractSession(size_t sessionId);

private:
    std::shared_ptr<ISessionRepository> repository;
};
