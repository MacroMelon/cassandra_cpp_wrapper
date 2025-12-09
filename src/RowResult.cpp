//
// Created by rin on 06/12/2025.
//

#include "../include/RowResult.h"

#include <iostream>

using namespace casswrap;

RowResult::RowResult(const CassResult* resultIn) {
    result = resultIn;
}

Row RowResult::fetchOne() {
    currentRow += 1;
    return Row(this, currentRow);
}

const CassRow* RowResult::getCassRowPtr(size_t rowIndex) {
    return cass_result_first_row(result);
}


RowResult::~RowResult() {
    cass_result_free(result);
}
