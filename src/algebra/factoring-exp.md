# Binary Exponentiation by Factoring

Binary exponentiation by factoring is a binary trick (*) which allows to
calculate $a^n$ using only $O(1)$ multiplications, instead of $O(log n)$
multiplications required by the classical binary exponentiation approach.

## Algorithm

Raising $a$ to the power of $n$ is expressed naively as the exponent
of the logarithm of $a$ multiplied by $n$ being the exponent.  In the
following examples all base numbers, $a$, are assumed to be odd.

## Implementation for 32-bit integers

### The logarithm table needed

```cpp
static const uint32_t mbin_log_32_table[32] = {
        0x00000000,
        0x00000000,
        0xd3cfd984,
        0x9ee62e18,
        0xe83d9070,
        0xb59e81e0,
        0xa17407c0,
        0xce601f80,
        0xf4807f00,
        0xe701fe00,
        0xbe07fc00,
        0xfc1ff800,
        0xf87ff000,
        0xf1ffe000,
        0xe7ffc000,
        0xdfff8000,
        0xffff0000,
        0xfffe0000,
        0xfffc0000,
        0xfff80000,
        0xfff00000,
        0xffe00000,
        0xffc00000,
        0xff800000,
        0xff000000,
        0xfe000000,
        0xfc000000,
        0xf8000000,
        0xf0000000,
        0xe0000000,
        0xc0000000,
        0x80000000,
};
```

### The logarithmic function

```cpp
static uint32_t
mbin_log_32(uint32_t r, uint32_t x)
{
        uint8_t n;

        for (n = 2; n != 16; n++) {
                if (x & (1 << n)) {
                        x = x + (x << n);
                        r -= mbin_log_32_table[n];
                }
        }

        r -= (x & 0xFFFF0000);

        return (r);
}
```

### The exponent function

```cpp
static uint32_t
mbin_exp_32(uint32_t r, uint32_t x)
{
        uint8_t n;

        for (n = 2; n != 16; n++) {
                if (x & (1 << n)) {
                        r = r + (r << n);
                        x -= mbin_log_32_table[n];
                }
        }

        r *= 1 - (x & 0xFFFF0000);

        return (r);
}
```

### The exponentiation function

```cpp
static uint32_t
mbin_power_odd_32(uint32_t rem, uint32_t base, uint32_t exp)
{
        if (base & 2) {
                /* divider is considered negative */
                base = -base;
                /* check if result should be negative */
                if (exp & 1)
                        rem = -rem;
        }
        return (mbin_exp_32(rem, mbin_log_32(0, base) * exp));
}
```

* [M30, Hans Petter Selasky, 2009](https://books.google.no/books?id=IkuEBAAAQBAJ&pg=PT310&lpg=PT310&dq=M30+selasky&source=bl&ots=W86b0P-yfw&sig=ACfU3U0Z7orvRJyZSGuUbOQ8H85sSpZHpQ&hl=no&sa=X&ved=2ahUKEwiC87OO1Zn3AhXrtYsKHTcIAgUQ6AF6BAgCEAM#v=onepage&q=M30%20selasky&f=false)
