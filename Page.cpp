#include "Page.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fcntl.h> //O_Create and O_Readonly
#include <iostream>
#include <stdexcept>
#include <unistd.h>
PageSize CreatePageInit() {
  PageSize p;
  p.header.page_id = 0;
  p.header.record_count = 0;
  p.header.version = 1;
  p.header.free_space_offset = sizeof(PageHeader);
  return p;
}
PageSize AddFileInit(PageSize p) {
  PageSize readMem;
  int fd = open("db.bin", O_CREAT | O_RDWR, 0644);
  if (fd < 0)
    return PageSize{};
  ssize_t wr = write(fd, &p, sizeof(PageSize));
  if (wr != sizeof(PageSize)) {
    close(fd);
    return PageSize{};
  }
  lseek(fd, 0, SEEK_SET);
  ssize_t rr = read(fd, &readMem, sizeof(PageSize));
  close(fd);
  if (rr != sizeof(PageSize)) {
    return PageSize{};
  }
  return readMem;
}
void insert_Record(PageSize &p, const char *text) {
  int fd = open("db.bin", O_CREAT | O_RDWR, 0644);
  if (fd < 0)
    throw std::runtime_error("Error in the file");
  int lenval = strlen(text); // strlen return type is size_t
  uint16_t sizecompr = static_cast<uint16_t>(
      lenval); // since format required is [05 00]=2 byte hence uint16_t used
  uint8_t *write_ptr = p.Datasize + p.header.free_space_offset;

  std::memcpy(write_ptr, &sizecompr, sizeof(sizecompr)); // adding 05 00 first
  std::memcpy(write_ptr + sizeof(sizecompr), text, static_cast<size_t>(lenval));
  p.header.record_count += 1;
  p.header.free_space_offset =
      p.header.free_space_offset + strlen(text) + sizeof(uint16_t);
  lseek(fd, p.header.free_space_offset, SEEK_SET);
  int wr = write(fd, write_ptr, sizeof(sizecompr) + lenval);

  close(fd);
}

void print_page_records(PageSize &page) {
  uint16_t offset = sizeof(PageHeader);
  uint16_t size;

  for (uint16_t i = 0; i < page.header.record_count; ++i) {
    std::memcpy(&size, page.Datasize + offset, sizeof(uint16_t));
    std::string Record(reinterpret_cast<char *>(page.Datasize + offset + 2),
                       size);
    offset = offset + size + 2;
    std::cout << Record << "\n";
  }
}
