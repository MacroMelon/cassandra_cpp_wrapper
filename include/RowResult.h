//
// Created by rin on 06/12/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_ROWRESULT_H
#define CASSANDRA_CPP_WRAPPER_ROWRESULT_H
#include "cassandra.h"
#include "Row.h"

namespace casswrap {
    class Row;
    class RowResult {
    public:
        RowResult(const CassResult* resultIn);
        Row fetchOne();
        size_t count();
        const CassRow* getCassRowPtr(size_t rowIndex);
        ~RowResult();

    private:
        const CassResult* result;
        size_t currentRow = 0;
    };
}

#endif //CASSANDRA_CPP_WRAPPER_ROWRESULT_H