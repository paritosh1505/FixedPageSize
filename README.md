crashdb
**<u>Phase 1</u>**  

Minimal storage engine prototype using 4096 byte fixed size pages.

**<u>Features</u>**

1.Fixed page size (4096 bytes)  
2.Page header with metadata  
3.Variable-length record storage  
4.Binary disk persistence (db.bin)  
5.Record decoding after reload

**<u>Page Format</u>**

<u>Header</u>

1. page_id
2. record_count
3. free_space_offset
4. reserved
5. Record layout:

