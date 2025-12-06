//
// Created by rin on 05/12/2025.
//

#include "../include/SqlStatement.h"

#include "Session.h"

using namespace casswrap;

SqlStatement::SqlStatement(Session* sessionIn, std::string query) {
    associatedSession = sessionIn->getCassSessionPtr();
    CassFuture* future = cass_session_prepare(associatedSession, query.c_str());

    if (cass_future_error_code(future) != CASS_OK) {
        //statement preparation failed
        //cass_future_free(future);
        const char* message;
        size_t message_length;
        cass_future_error_message(future, &message, &message_length);
        std::cout << "Statement preparation failed: " << message << std::endl;
        cass_future_free(future);
        throw;
    }

    preparedStatement = cass_prepared_bind(cass_future_get_prepared(future));

    cass_future_free(future);
}

RowResult SqlStatement::execute() {
    CassFuture* future = cass_session_execute(associatedSession, preparedStatement);
    if (cass_future_error_code(future) != CASS_OK) {
        //error in execution
        throw 2;
    }
    return RowResult(cass_future_get_result(future));
}

SqlStatement::~SqlStatement() {
    cass_statement_free(preparedStatement);
}