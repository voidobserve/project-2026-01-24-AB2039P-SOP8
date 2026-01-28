#ifndef _API_RING_BUF_H
#define _API_RING_BUF_H


typedef struct{
    uint8_t *buf;
    uint32_t buf_read;
    uint32_t buf_write;
    uint32_t data_len;
    uint32_t total_len;
}ring_buf_t;


void ring_buf_init(ring_buf_t *ring_buf, uint8_t *buffer, uint32_t size);

void ring_buf_clear(ring_buf_t *ring_buf);

uint32_t ring_buf_write(ring_buf_t *ring_buf, uint8_t *buffer, uint32_t size);

uint32_t ring_buf_read(ring_buf_t *ring_buf, uint8_t *buffer, uint32_t size);

uint8_t* ring_buf_get(ring_buf_t *ring_buf, uint32_t size);


#endif // _API_RING_BUF_H
