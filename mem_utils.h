#include <inttypes.h>
typedef struct mem_transaction{
    time_t epoch_time;
    uint64_t addr;
    uint32_t prev;
    uint32_t next;
} mem_transaction;
