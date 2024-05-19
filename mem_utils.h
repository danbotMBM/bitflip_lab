struct mem_transaction{
    time_t epoch_time;
    uint32_t addr;
    uint32_t prev;
    uint32_t new;
};
typedef struct mem_transcation mem_transaction;
#define TRUE 1
#define FALSE 0
#define bool int
