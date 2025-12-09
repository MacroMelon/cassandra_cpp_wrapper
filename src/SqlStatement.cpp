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
        const char* message;
        size_t message_length;
        cass_future_error_message(future, &message, &message_length);
        std::cout << "Unable to execute: " << message << std::endl;
        throw 2;
    }
    const CassResult *ret = cass_future_get_result(future);
    cass_future_free(future);
    return RowResult(ret);
}

void SqlStatement::executeAsync() {
    executeAsyncFuture = cass_session_execute(associatedSession, preparedStatement);
}

RowResult SqlStatement::executeAsyncWaitGetResult() {
    if (executeAsyncFuture == nullptr) {
        std::cout << "executeAsyncFuture NULL, executeAsync() must be called before executeAsyncWaitGetResult()!" << std::endl;
        throw;
    }
    if (cass_future_error_code(executeAsyncFuture) != CASS_OK) {
        //error in execution
        const char* message;
        size_t message_length;
        cass_future_error_message(executeAsyncFuture, &message, &message_length);
        std::cout << "Unable to execute: " << message << std::endl;
        throw 2;
    }
    const CassResult *ret = cass_future_get_result(executeAsyncFuture);
    cass_future_free(executeAsyncFuture);
    return RowResult(ret);
}

//int64
SqlStatement SqlStatement::bind(std::string parameterName, int64_t value) {
    cass_statement_bind_int64_by_name(preparedStatement, parameterName.c_str(), value);
    return *this;
}

SqlStatement SqlStatement::bind(size_t index, int64_t value) {
    cass_statement_bind_int64(preparedStatement, index, value);
    return *this;
}

SqlStatement SqlStatement::bind(int64_t value) {
    cass_statement_bind_int64(preparedStatement, currentBindIndex, value);
    currentBindIndex++;
    return *this;
}

//uint32
SqlStatement SqlStatement::bind(std::string parameterName, uint32_t value) {
    cass_statement_bind_uint32_by_name(preparedStatement, parameterName.c_str(), value);
    return *this;
}

SqlStatement SqlStatement::bind(size_t index, uint32_t value) {
    cass_statement_bind_uint32(preparedStatement, index, value);
    return *this;
}

SqlStatement SqlStatement::bind(uint32_t value) {
    cass_statement_bind_uint32(preparedStatement, currentBindIndex, value);
    currentBindIndex++;
    return *this;
}

//int32
SqlStatement SqlStatement::bind(std::string parameterName, int32_t value) {
    cass_statement_bind_int32_by_name(preparedStatement, parameterName.c_str(), value);
    return *this;
}

SqlStatement SqlStatement::bind(size_t index, int32_t value) {
    cass_statement_bind_int32(preparedStatement, index, value);
    return *this;
}

SqlStatement SqlStatement::bind(int32_t value) {
    cass_statement_bind_int32(preparedStatement, currentBindIndex, value);
    currentBindIndex++;
    return *this;
}

//uuid
SqlStatement SqlStatement::bindUUID(std::string parameterName, std::string uuid) {
    CassUuid cassUUID;
    cass_uuid_from_string(uuid.c_str(), &cassUUID);
    cass_statement_bind_uuid_by_name(preparedStatement, parameterName.c_str(), cassUUID);
    return *this;
}

SqlStatement SqlStatement::bindUUID(size_t index, std::string uuid) {
    CassUuid cassUUID;
    cass_uuid_from_string(uuid.c_str(), &cassUUID);
    cass_statement_bind_uuid(preparedStatement, index, cassUUID);
    return *this;
}

SqlStatement SqlStatement::bindUUID(std::string uuid) {
    CassUuid cassUUID;
    cass_uuid_from_string(uuid.c_str(), &cassUUID);
    cass_statement_bind_uuid(preparedStatement, currentBindIndex, cassUUID);
    currentBindIndex++;
    return *this;
}

SqlStatement::~SqlStatement() {
    //free executeAsyncFuture?
    cass_statement_free(preparedStatement);
}