#pragma once
#include <cstddef>
#include <cstdint>
constexpr size_t PAGE_SIZE = 4096;
constexpr size_t PAGE_HEADER = 16;
struct PageHeader {
  uint32_t page_id;
  uint32_t reserved;
  uint16_t record_count;
  uint16_t free_space_offset;
  uint16_t version;
};

struct PageSize {
  PageHeader header;
  uint8_t Datasize[PAGE_SIZE - sizeof(PageHeader)];
};
static_assert(sizeof(PageSize) == PAGE_SIZE,
              "Page size should be equal to 4096 byte");
static_assert(sizeof(PageHeader) == PAGE_HEADER,
              "Page header layout is changed");
PageSize CreatePageInit();
PageSize AddFileInit(PageSize);
void insert_Record(PageSize &, const char *);
void print_page_records(PageSize &);
void test(PageSize p);