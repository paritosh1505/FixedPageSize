#pragma once
#include <cstddef>
#include <cstdint>
const size_t PAGE_SIZE = 4096;
struct PageHeader {
  uint32_t page_id;
  uint16_t record_count;
  uint16_t free_space_offset;
  uint32_t reserved;
};

struct PageSize {
  PageHeader header;
  uint8_t Datasize[PAGE_SIZE - sizeof(PageHeader)];
};

PageSize CreatePageInit();
PageSize AddFileInit(PageSize);
void insert_Record(PageSize &, const char *);
void print_page_records(PageSize &);
int test();