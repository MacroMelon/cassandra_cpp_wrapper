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


        SqlStatement bind(std::string parameterName, int64_t value);
        SqlStatement bind(size_t index, int64_t value);
        SqlStatement bind(int64_t value);

        SqlStatement bind(std::string parameterName, int32_t value);
        SqlStatement bind(size_t index, int32_t value);
        SqlStatement bind(int32_t value);

        ~SqlStatement();

    private:
        size_t currentBindIndex = 0;
        CassSession* associatedSession;
        CassStatement* preparedStatement;
    };
}


#endif //CASSANDRA_CPP_WRAPPER_SQLSTATEMENT_H