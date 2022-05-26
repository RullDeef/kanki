#pragma once

#include <list>
#include <string>
#include "core/isessionrepository.hpp"

class FileSessionRepository : public ISessionRepository
{
public:
    FileSessionRepository(const std::string &filename);
    ~FileSessionRepository();

    virtual std::list<Session> getSessions() override;
    virtual Session getSession(size_t id) override;
    virtual void removeSession(size_t id) override;
    virtual void saveSession(const Session &session) override;

    /// WARNING: not tested at all
    void load();
    void dump();

private:
    std::string filename;
    std::list<Session> sessions;
};
