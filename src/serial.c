void putc(int data) {
    char *address = 0x3F215040;
    *address = data;
}
