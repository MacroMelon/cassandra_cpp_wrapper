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
    //todo - properly handle this like mysql devapi
    if (cass_result_row_count(result) >= currentRow) throw 5;
    return Row(this, currentRow);
}

size_t RowResult::count() {
    return cass_result_row_count(result);
}

const CassRow* RowResult::getCassRowPtr(size_t rowIndex) {
    return cass_result_first_row(result);
}


RowResult::~RowResult() {
    cass_result_free(result);
}
