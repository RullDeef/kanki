#pragma once

#include <list>
#include <string>
#include <memory>
#include "core/isessionrepository.hpp"
#include "db/idbiofactory.hpp"

class FileSessionRepository : public ISessionRepository
{
public:
    FileSessionRepository(std::shared_ptr<IDTOIOFactory> ioFactory = nullptr);
    ~FileSessionRepository();

    void load();
    void load(IDBReader &reader);

    void dump();
    void dump(IDBWriter &writer);

    virtual std::list<Session> getSessions() override;
    virtual Session getSession(UUID id) override;
    virtual void removeSession(UUID id) override;
    virtual void saveSession(const Session &session) override;

private:
    std::list<Session> sessions;
    std::shared_ptr<IDTOIOFactory> ioFactory;
};
