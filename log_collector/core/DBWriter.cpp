#include "DBWriter.hpp"
#include "MessageQueue.hpp"
#include "LogEntry.hpp"
#include <pqxx/pqxx>

DBWriter::DBWriter(MessageQueue<LogEntry>& queue) :
queue(queue), running(false) {}

DBWriter::~DBWriter() {
    stop();
}

void DBWriter::start() {
    running = true;
    worker = std::thread(&DBWriter::run, this);
}

void DBWriter::stop() {
    bool wasRunning = running.exchange(false);
    if (wasRunning) {
        queue.push(LogEntry{}); // wake the worker so it can exit
        if(worker.joinable()) 
            worker.join();
    }
}

void DBWriter::run() {
    try{
        pqxx::connection conn(
            "dbname=logs user=postgres password=postgres host=log_postgres port=5432"
        );
        std::cout << "[DBWriter] connected to PostgresSQL." << std::endl;

        while(true) {
            auto log = queue.pop();
            if(!running) break;
            
            try {
                pqxx::work txn(conn);

                txn.exec_params(
                    "INSERT INTO logs (timestamp, level, host, pid, message) VALUES ($1, $2, $3, $4, $5)",
                    log.timestamp,
                    log.level,
                    log.host,
                    log.pid,
                    log.message
                );

                txn.commit();
                std::cout << "[DB-INSERT] ok: " << log << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "[DBWriter] Insert failed: " << e.what() << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[DBWriter] Insert failed: " << e.what() << std::endl;
    }
}
