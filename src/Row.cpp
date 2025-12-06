//
// Created by rin on 06/12/2025.
//

#include "../include/Row.h"

#include <iostream>

using namespace casswrap;

Row::Row(RowResult* resultIn, size_t rowIndex){
    row = resultIn->getCassRowPtr(rowIndex);
}

Value Row::operator[](size_t index) {
    return Value(this, index);
}

Value Row::operator[](std::string columnName) {
    return Value(this, columnName);
}

const CassValue* Row::getCassValuePtr(size_t index) {
    return cass_row_get_column(row, index);
}

const CassValue* Row::getCassValuePtr(std::string columnName) {
    return cass_row_get_column_by_name(row, columnName.c_str());
}
