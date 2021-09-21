# ringBuffer
A fast, type agnostic ring buffer that's easy to use.

<br/>

## Getting started
### Include header
`#include "ringBuffer.h"`

### Compile with OpenMP support
Use the `-fopenmp` flag with GCC or LLVM/Clang.

<br/>

## API reference
<br/>

[`rb_create()`](#rb_create)
[`rb_destroy()`](#rb_destroy)
[`rb_write()`](#rb_write)
[`rb_overWrite()`](#rb_overwrite)
[`rb_read()`](#rb_read)
[`rb_dump()`](#rb_dump)
[`rb_reset()`](#rb_reset)
[`rb_fillLevel()`](#rb_filllevel)

<br/>

#### `rb_create()`
Create a ringBuffer.
```C
ringBuffer* rb_create(size_t len, size_t size)
```
##### Value
```
Returns pointer to new ringBuffer. Otherwise returns NULL if memory allocation failed.
```
##### Arguments
```
len   :  Max number of elements the ringBuffer can hold. If len is not a power of 2, it will be 
         automatically rounded up to the next greater power of 2 for speed.
```
```
size  :  Size in bytes of each element.
```

<br/>

---

<br/>

#### `rb_destroy()`
Free memory allocated for a ringBuffer.
```C
void rb_destroy(ringBuffer* r)
```
##### Arguments
```
r  :  Pointer returned by rb_create().
```

<br/>

---

<br/>

#### `rb_write()`
Write an element into a ringBuffer, without overwriting. If the ringBuffer is full, `rb_write()` does nothing.
```C
void rb_write(ringBuffer* r, void* src)
```
##### Arguments
```
r    :  Pointer returned by rb_create().
```
```
src  :  Pointer to data that will be copied into the ringBuffer. r→size number of bytes will be copied.
```

<br/>

---

<br/>

#### `rb_overWrite()`
Write an element into a ringBuffer, with overwriting. If the ringBuffer is full, the oldest element will be overwritten.
```C
void rb_overWrite(ringBuffer* r, void* src)
```
##### Arguments
```
r    :  Pointer returned by rb_create().
```
```
src  :  Pointer to data that will be copied into the ringBuffer. r→size number of bytes will be copied.
```

<br/>

---

<br/>

#### `rb_read()`
Read oldest element from a ringBuffer.
```C
void rb_read(ringBuffer* r, void* dest)
```
##### Arguments
```
r     :  Pointer returned by rb_create().
```
```
dest  :  Pointer to location where the element will be copied to. r→size number of bytes will be copied.
```

<br/>

---

<br/>

#### `rb_dump()`
Parallelized read of all elements stored in a ringBuffer. Unlike after calling `rb_read()`, elements remain in the buffer.
```C
void rb_dump(ringBuffer* r, void* dest)
```
##### Arguments
```
r     :  Pointer returned by rb_create().
```
```
dest  :  Pointer to location where the elements will be copied to. r→size * rb_fillLevel(r) number of bytes will be copied.
         Therefore, r→size determines data alignment at dest.
```

<br/>

---

<br/>

#### `rb_reset()`
Remove all elements held in a ringBuffer.
```C
void rb_reset(ringBuffer* r)
```
##### Arguments
```
r  :  Pointer returned by rb_create().
```

<br/>

---

<br/>

#### `rb_fillLevel()`
Get number of elements held in a ringBuffer.
```C
size_t rb_fillLevel(ringBuffer* r)
```
##### Value
```
Returns size_t x, where 0 ≤ x ≤ r→len.
```
##### Arguments
```
r  :  Pointer returned by rb_create().
```

<br/><br/>

## Licence
[![WTFPL](https://upload.wikimedia.org/wikipedia/commons/0/0a/WTFPL_badge.svg)](http://www.wtfpl.net/)  
This project is licenced under the WTFPLv2 — see the [COPYING](COPYING) file for details  
Copyright © 2021 Andre Ostrovsky
