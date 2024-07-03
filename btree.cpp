#include "btree.h"

#include <cstdint>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

I64 &Value::as_i64() {
    return std::get<I64>(value);
}

LongBlob &Value::as_longblob() {
    return std::get<LongBlob>(value);
}

Storage::Storage(int fd) {
}

/*
    BTree Internals to help with our own management
*/

struct BEntry {
    BType key_type;
    BType value_type;
};

struct BTreeValue {};

struct BTreeNode {
    uint64_t size_num_keys;
};

// Simple Btree that indexes all other BTrees
struct BaseTree {};

std::expected<Storage, BOpenError>
Storage::bopen(std::filesystem::path filename) {
    int fd = ::open(filename.c_str(), O_RDWR | O_CREAT, 0644);
    if (-1 == fd) {
        return std::unexpected(BOpenError{errno});
    }

    // read out the first BTree

    // build the ref count table

    // read the btree of btrees here
    return Storage(fd);
}

Storage::~Storage() {
}