typedef struct {
    size_t head;
    size_t tail;
    size_t len;
    size_t size;
    char A[];
} ringBuffer;

ringBuffer* rb_create(size_t len, size_t size);
//  Create a ringBuffer.
/*  Arguments --------------------------------------------------------------
    size_t len   :  Max number of elements the ringBuffer can hold.
                    If len is not a power of 2, it will be automatically
                    rounded up to the next greater power of 2 for speed.
    size_t size  :  Size in bytes of each element.
    Value ------------------------------------------------------------------
    Returns pointer to new ringBuffer. Otherwise returns NULL if memory
    allocation failed.
*/

void rb_destroy(ringBuffer* r);
//  Free memory allocated for a ringBuffer.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
*/

void rb_write(ringBuffer* r, void* src);
//  Write an element into a ringBuffer, without overwriting.
//  If the ringBuffer is full, rb_write() does nothing.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
    void* src      :  Pointer to data that will be copied into the ringBuffer.
                      r->size number of bytes will be copied.
*/

void rb_overWrite(ringBuffer* r, void* src);
//  Write an element into a ringBuffer, with overwriting.
//  If the ringBuffer is full, the oldest element will be overwritten.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
    void* src      :  Pointer to data that will be copied into the ringBuffer.
                      r->size number of bytes will be copied.
*/

void rb_read(ringBuffer* r, void* dest);
//  Read oldest element from a ringBuffer.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
    void* dest     :  Pointer to location where the element will be copied to.
                      r->size number of bytes will be copied.
*/

void rb_dump(ringBuffer* r, void* dest);
//  Parallelized read of all elements stored in a ringBuffer.
//  Unlike after calling rb_read(), elements remain in the buffer.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
    void* dest     :  Pointer to location where the elements will be copied to.
                      r->size * rb_fillLevel(r) number of bytes will be copied.
                      Therefore, r->size determines data alignment at dest.
*/

void rb_reset(ringBuffer* r);
//  Remove all elements held in a ringBuffer.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
*/

size_t rb_fillLevel(ringBuffer* r);
//  Get number of elements held in a ringBuffer.
/*  Arguments --------------------------------------------------------------
    ringBuffer* r  :  Pointer returned by rb_create().
    Value ------------------------------------------------------------------
    Returns size_t x, where 0 <= x <= r->len.
*/
