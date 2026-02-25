#pragma once
#include <cstddef>
#include <cstdint>
#include <type_traits>
constexpr size_t PAGE_SIZE = 4096;
constexpr size_t PAGE_HEADER = 24;
struct PageHeader {
  uint64_t page_lsn;
  uint32_t page_id;
  uint16_t record_count;
  uint16_t free_space_offset;
  uint16_t page_version;
  uint8_t page_type;
  uint8_t reserved[5];
};

struct PageSize {
  PageHeader header;
  uint8_t Datasize[PAGE_SIZE - sizeof(PageHeader)];
};
static_assert(sizeof(PageSize) == PAGE_SIZE,
              "Page size should be equal to 4096 byte");
static_assert(sizeof(PageHeader) == PAGE_HEADER,
              "Page header layout is changed");
static_assert(std::is_standard_layout_v<PageHeader>);
static_assert(std::is_standard_layout_v<PageSize>);
static_assert(std::is_trivially_copyable_v<PageSize>);
static_assert(std::is_trivially_copyable_v<PageSize>);

PageSize CreatePageInit();
PageSize AddFileInit(PageSize);
void insert_Record(PageSize &, const char *);
void print_page_records(PageSize &);
void test(PageSize p);