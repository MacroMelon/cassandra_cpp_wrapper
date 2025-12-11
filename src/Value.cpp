//
// Created by rin on 06/12/2025.
//

#include "../include/Value.h"

#include <iostream>

using namespace casswrap;

Value::Value(Row* rowIn, size_t index) {
    value = rowIn->getCassValuePtr(index);
}

Value::Value(Row* rowIn, std::string columnName) {
    value = rowIn->getCassValuePtr(columnName);
}

std::string Value::getString() {
    const char* output;
    size_t message_length;
    if (cass_value_get_string(value, &output, &message_length) != CASS_OK) {
        //error
        throw 3;
    }
    return std::string(output, message_length);
}

uint32_t Value::getUint32() {
    uint32_t output;
    if (cass_value_get_uint32(value, &output) != CASS_OK) {
        //error
        throw 3;
    }
    return output;
}

int32_t Value::getInt32() {
    int32_t output;
    if (cass_value_get_int32(value, &output) != CASS_OK) {
        //error
        throw 3;
    }
    return output;
}

int64_t Value::getInt64() {
    int64_t output;
    if (cass_value_get_int64(value, &output) != CASS_OK) {
        //error
        throw 3;
    }
    return output;
}

double Value::getDouble() {
    double output;
    if (cass_value_get_double(value, &output) != CASS_OK) {
        //error
        throw 3;
    }
    return output;
}

/*
template <>
std::string Value::get<std::string>() {
    const char* output;
    size_t message_length;
    if (cass_value_get_string(value, &output, &message_length) != CASS_OK) {
        //error
        throw 3;
    }
    return std::string(output, message_length);
}

template <>
uint32_t Value::get<uint32_t>() {
    uint32_t output;
    if (cass_value_get_uint32(value, &output) != CASS_OK) {
        //error
        throw 3;
    }
    return output;
}

template <>
int64_t Value::get<int64_t>() {
    int64_t output;
    if (cass_value_get_int64(value, &output) != CASS_OK) {
        //error
        throw 3;
    }
    return output;
}
*/

