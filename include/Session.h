//
// Created by rin on 23/11/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_SESSION_H
#define CASSANDRA_CPP_WRAPPER_SESSION_H

#include <cassandra.h>
#include <string>

namespace casswrap {
    class Session {
    public:
        Session(const std::string& host);
    private:
        CassFuture* connect_future = nullptr;
        CassCluster* cluster = cass_cluster_new();
        CassSession* session = cass_session_new();
    };
} // casswrap

#endif //CASSANDRA_CPP_WRAPPER_SESSION_H