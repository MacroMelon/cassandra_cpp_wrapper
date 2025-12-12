//
// Created by rin on 05/12/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_SQLSTATEMENT_H
#define CASSANDRA_CPP_WRAPPER_SQLSTATEMENT_H

#include <cassandra.h>
#include <RowResult.h>
#include <string>

//TODO - Use shared pointer for the associated session pointer
//TODO - bind() functionality like mysql xdevapi
//TODO - batch statements

namespace casswrap {
    class Session;
    class SqlStatement {
    public:
        SqlStatement(Session* sessionIn, std::string query);

        RowResult execute();
        void executeAsync();
        RowResult executeAsyncWaitGetResult();

        SqlStatement& bind(std::string parameterName, int64_t value);
        SqlStatement& bind(size_t index, int64_t value);
        SqlStatement& bind(int64_t value);

        SqlStatement& bind(std::string parameterName, uint32_t value);
        SqlStatement& bind(size_t index, uint32_t value);
        SqlStatement& bind(uint32_t value);

        SqlStatement& bind(std::string parameterName, int32_t value);
        SqlStatement& bind(size_t index, int32_t value);
        SqlStatement& bind(int32_t value);

        SqlStatement& bind(std::string parameterName, double value);
        SqlStatement& bind(size_t index, double value);
        SqlStatement& bind(double value);

        SqlStatement& bindUUID(std::string parameterName, std::string uuid);
        SqlStatement& bindUUID(size_t index, std::string uuid);
        SqlStatement& bindUUID(std::string uuid);

        ~SqlStatement();

    private:
        size_t currentBindIndex = 0;
        CassSession* associatedSession;
        CassStatement* preparedStatement;
        CassFuture* executeAsyncFuture;
    };
}


#endif //CASSANDRA_CPP_WRAPPER_SQLSTATEMENT_H