//
// Created by rin on 23/11/2025.
//

#include "../include/Session.h"

using namespace casswrap;

Session::Session(SessionSettings connectionSettings) {

    /* Setup and connect to cluster */

    //std::unique_ptr<CassCluster, cass_cluster_free> cluster (cass_cluster_new());
    //session =  std::unique_ptr<CassSession, cass_session_free>(cass_session_new());
    session = cass_session_new();
    //does this have to be outside?
    cluster = cass_cluster_new();
    //CassSsl* ssl = cass_ssl_new();

    /* Add contact points */
    cass_cluster_set_contact_points(cluster, connectionSettings.host.c_str());

    // Disable certifcate verifcation
    //cass_ssl_set_verify_flags(ssl, CASS_SSL_VERIFY_NONE);

    //cass_cluster_set_ssl(cluster, ssl);

    cass_cluster_set_credentials(cluster, connectionSettings.user.c_str(), connectionSettings.password.c_str());

    CassFuture* connect_future;

    /* Provide the cluster object as configuration to connect the session */
    if (connectionSettings.keyspace.empty()) {
        connect_future = cass_session_connect(session, cluster);
    }
    else {
        connect_future = cass_session_connect_keyspace(session, cluster, connectionSettings.keyspace.c_str());
    }

    if (cass_future_error_code(connect_future) != CASS_OK) {
        //connection failed
        //throw error
        /* Handle error */
        const char* message;
        size_t message_length;
        cass_future_error_message(connect_future, &message, &message_length);
        std::cout << "Unable to connect: " << message << std::endl;
        cass_session_free(session);
        cass_cluster_free(cluster);
        cass_future_free(connect_future);
        throw;
    }

    cass_future_free(connect_future);

    std::cout << "Successfully connected!" << std::endl;
}

CassSession* Session::getCassSessionPtr() {
    return session;
}


SqlStatement Session::sql(std::string sqlString) {
    return SqlStatement(this, sqlString);
}

Session::~Session() {
    cass_session_free(session);
    cass_cluster_free(cluster);
}