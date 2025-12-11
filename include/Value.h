//
// Created by rin on 06/12/2025.
//

#ifndef CASSANDRA_CPP_WRAPPER_VALUE_H
#define CASSANDRA_CPP_WRAPPER_VALUE_H

#include "cassandra.h"
#include "Row.h"
#include <string>

namespace casswrap {
    class Row;
    class Value {
    public:
        Value(Row* rowIn, size_t index);
        Value(Row* rowIn, std::string columnName);

        std::string getString();
        uint32_t getUint32();
        int32_t getInt32();
        int64_t getInt64();
        double getDouble();
        /*
        template <typename T> T get();
        template <> std::string get<std::string>();
        template <> uint32_t get<uint32_t>();
        template <> int64_t get<int64_t>();
        */
    private:
        const CassValue* value;
    };
}


#endif //CASSANDRA_CPP_WRAPPER_VALUE_H