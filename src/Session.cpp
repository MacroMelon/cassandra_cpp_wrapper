//
// Created by rin on 23/11/2025.
//

#include "Session.h"

namespace casswrap {
    Session::Session(const std::string& host) {
        /* Setup and connect to cluster */
        CassFuture* connect_future = nullptr;
        CassCluster* cluster = cass_cluster_new();
        CassSession* session = cass_session_new();

        /* Add contact points */
        cass_cluster_set_contact_points(cluster, host.c_str());

        /* Provide the cluster object as configuration to connect the session */
        connect_future = cass_session_connect(session, cluster);

        if (cass_future_error_code(connect_future) != CASS_OK) {
        }
    }
} // casswrap