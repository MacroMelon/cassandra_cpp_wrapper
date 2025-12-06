//
// Created by rin on 06/12/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_RESULT_H
#define CASSANDRA_CPP_WRAPPER_RESULT_H

#include <string>
#include "cassandra.h"
#include "Value.h"
#include "RowResult.h"

namespace casswrap {
    class RowResult;
    class Value;
    class Row {
    public:
        Row(RowResult* resultIn, size_t rowIndex);
        Value operator[](size_t index);
        Value operator[](std::string columnName);
        const CassValue* getCassValuePtr(size_t index);
        const CassValue* getCassValuePtr(std::string columnName);
    private:
        const CassRow* row;
    };
}


#endif //CASSANDRA_CPP_WRAPPER_RESULT_H