#pragma once

#include <algorithm>
#include <stdexcept>
#include <list>
#include "tools/logger.hpp"
#include "core/isessionrepository.hpp"

class FileSessionRepository : public ISessionRepository
{
public:
    FileSessionRepository(const std::string& filename)
        : filename(filename)
    {
        try { load(); }
        catch (const std::exception& e) {
            ERROR_METHOD(e.what());
        }
    }

    ~FileSessionRepository() {
        try { dump(); }
        catch (const std::exception& e) {
            ERROR_METHOD(e.what());
        }
    }

    virtual std::list<Session> getSessions() override { return sessions; }

    virtual Session getSession(size_t id) override {
        auto iter = std::find_if(sessions.begin(), sessions.end(),
            [id](const Session& session) { return session.getId() == id; });

        if (iter == sessions.end())
            throw std::runtime_error("invalid id");
        return *iter;        
    }

    virtual void removeSession(size_t id) override {
        sessions.erase(
            std::remove_if(sessions.begin(), sessions.end(),
                [id](const Session& session) { return session.getId() == id; }),
            sessions.end());
    }

    virtual void saveSession(const Session& session) override {
        size_t id = session.getId();
        auto iter = std::find_if(sessions.begin(), sessions.end(),
            [id](const Session& session) { return session.getId() == id; });
        
        if (iter != sessions.end())
            *iter = session;
        else
            sessions.push_back(session);
    }

    ///WARNING: not tested at all
    void load() {
        ///TODO: implement correctly
        std::wifstream file(filename);

        if (!file)
            throw std::runtime_error("bad filename");

        sessions.clear();
        IdGenerator idGenerator;

        do {
            size_t sessionId;
            size_t snapshotsCount = 0;

            time_t start_time_t, end_time_t;

            file >> sessionId >> std::ws;
            file >> start_time_t >> std::ws;
            file >> end_time_t >> std::ws;
            file >> snapshotsCount >> std::ws;

            auto startTime = std::chrono::system_clock::from_time_t(start_time_t);
            auto endTime = std::chrono::system_clock::from_time_t(end_time_t);

            Session session(idGenerator(), startTime, endTime);
            for (size_t i = 0; i < snapshotsCount; i++) {
                std::wstring symbol, reading, description;
                std::getline(file, symbol);
                std::getline(file, reading);
                std::getline(file, description);

                int paramTypeInt;
                file >> paramTypeInt >> std::ws;
                Snapshot::ParamType paramType = paramTypeInt == 0 ?
                    Snapshot::ParamType::READING :
                    Snapshot::ParamType::TRANSLATION;
                
                int degree;
                file >> degree >> std::ws;

                time_t time_point_t;
                file >> time_point_t >> std::ws;

                auto timePoint = std::chrono::system_clock::from_time_t(time_point_t);
                
                Card card(idGenerator(), symbol, reading, description);
                session.addSnapshot(Snapshot(card, paramType, degree, timePoint));
            }
            file >> std::ws;
            sessions.push_back(std::move(session));
        } while (!file.eof());
    }

    void dump() {
        ///TODO: implement correctly
        std::wofstream file(filename);

        if (!file)
            throw std::runtime_error("bad filename");

        for (const auto& session : sessions)
        {
            file << session.getId() << std::endl;
            file << std::chrono::system_clock::to_time_t(session.getStartTime()) << std::endl;
            file << std::chrono::system_clock::to_time_t(session.getEndTime()) << std::endl;
            file << session.size() << std::endl;

            for (const auto& snapshot : session)
            {
                file << snapshot.getCard().getSymbol() << std::endl;
                file << snapshot.getCard().getReading() << std::endl;
                file << snapshot.getCard().getDescription() << std::endl;

                if (snapshot.getParamType() == Snapshot::ParamType::READING)
                    file << 0 << std::endl;
                else
                    file << 1 << std::endl;
                
                file << snapshot.getKnowledgeDegree() << std::endl;
                file << std::chrono::system_clock::to_time_t(snapshot.getTimePoint()) << std::endl;
            }
        }
    }

private:
    std::string filename;
    std::list<Session> sessions;
};
