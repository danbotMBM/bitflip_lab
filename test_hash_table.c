#include "hash_table.c"

int main(void* args){
    hash_node** table = make_table();
    int error_status = 0;
    printf("%u\n", set_val(table, 1000, 1001, &error_status));
    printf("%u\n", set_val(table, 1001, 1001, &error_status));
    printf("%u\n", set_val(table, 1002, 1001, &error_status));
    printf("%u\n", set_val(table, 1300, 1001, &error_status));
    printf("%u\n", set_val(table, 1000, 1001, &error_status));
    printf("%u\n", get_val(table, 1002, &error_status));
    printf("%u\n", set_val(table, 1300, 1001, &error_status));
    print_hash_table(table);
    printf("%u\n", remove_key(table, 1000, &error_status));
    printf("%u\n", set_val(table, 1300, 1001, &error_status));
    printf("%u\n", set_val(table, 1000, 1001, &error_status));
    printf("%u\n", set_val(table, 1200, 1001, &error_status));
    print_hash_table(table);
    printf("%u\n", remove_key(table, 1200, &error_status));
    print_hash_table(table);
    printf("%u\n", remove_key(table, 1300, &error_status));
    print_hash_table(table);
    printf("%u\n", remove_key(table, 1000, &error_status));
    print_hash_table(table);
}