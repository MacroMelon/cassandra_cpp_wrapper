//
// Created by rin on 23/11/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_SESSION_H
#define CASSANDRA_CPP_WRAPPER_SESSION_H

#include <cassandra.h>
#include <string>
#include <memory>
#include "SqlStatement.h"
#include "settings.h"
#include "Value.h"

#include <iostream>

//TODO - use smart pointers
//TODO - SSL

//A memory safe(?) wrapper for the CassSession object that implements RAII

namespace casswrap {
    class SqlStatement;
    class Session {
    public:
        Session(SessionSettings connectionSettings);
        ~Session();
        SqlStatement sql(std::string sqlString);
        CassSession* getCassSessionPtr();
    private:
        //std::unique_ptr<CassSession, void(*)(cass_session_free*)> session;
        CassSession* session;
        CassCluster* cluster;
    };
}

#endif //CASSANDRA_CPP_WRAPPER_SESSION_H