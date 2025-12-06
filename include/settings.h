//
// Created by rin on 06/12/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_SETTINGS_H
#define CASSANDRA_CPP_WRAPPER_SETTINGS_H

namespace casswrap {
    struct SessionSettings {
        std::string host;
        uint_fast16_t port;
        std::string user;
        std::string password;
        std::string database;
    };
}
#endif //CASSANDRA_CPP_WRAPPER_SETTINGS_H