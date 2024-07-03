#pragma once

#include <expected>
#include <filesystem>
#include <variant>
#include <vector>

enum class TypeType : uint16_t {
    NONE__,
    LONGBLOB,
    INT64,
    BENT__ = (uint16_t)-1,
};

struct Type {
    TypeType type_type;
    uint16_t type_size = 0;
};

struct BType {
    Type key_type;
    Type value_type;
};

struct LongBlob {
    uint64_t hash;
    std::vector<uint8_t> blob;
};

struct I64 {
    uint64_t value;
};

struct Value {
    std::variant<LongBlob, I64> value;

    I64 &as_i64();
    LongBlob &as_longblob();
};

struct BOpenError {
    int open_errno;
};

class Storage {
  public:
    class BTree;

  private:
    int fd;
    BTree *bptr;
    // ... refcounts and stuff

    Storage(int fd);

  public:
    ~Storage();

    std::expected<BTree, BOpenError> get_btree(size_t btree_idx);
    void create_btree(size_t btree_idx, BType btree_type);
    void delete_btree(size_t btree_idx);

    class BTree {
        Storage *storage;
        size_t btree_idx;

      public:
        Value get(Value key) const;
        void set(Value key, Value value);
        void remove(Value key);
        size_t size() const;
        bool empty() const;
        size_t rank(Value key) const;
        Value select(size_t rank) const;
    };
    static std::expected<Storage, BOpenError>
    bopen(std::filesystem::path filename);
};
