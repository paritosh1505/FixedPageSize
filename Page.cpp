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
  size_t lenval = strlen(text);
  uint16_t sizecompr = static_cast<uint16_t>(lenval);
  std::cout << "*******" << p.header.free_space_offset << "####" << "\n";
  uint8_t *write_ptr = p.Datasize + p.header.free_space_offset;

  std::memcpy(write_ptr, &sizecompr, sizeof(sizecompr));
  std::memcpy(write_ptr + sizeof(sizecompr), text, static_cast<size_t>(lenval));
  std::cout << "*******" << write_ptr << "\n";
  p.header.record_count += 1;
  std::cout << "*******" << p.header.free_space_offset << "####" << "\n";

  p.header.free_space_offset =
      p.header.free_space_offset + strlen(text) + sizeof(uint16_t);
  lseek(fd, p.header.free_space_offset, SEEK_SET);
  int wr = write(fd, write_ptr, sizeof(sizecompr) + lenval);

  close(fd);
}