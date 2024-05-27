typedef struct mem_transaction{
    time_t epoch_time;
    uint32_t addr;
    uint32_t prev;
    uint32_t next;
} mem_transaction;
