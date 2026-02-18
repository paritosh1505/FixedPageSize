#include "Page.hpp"
#include <fcntl.h> //O_Create and O_Readonly
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