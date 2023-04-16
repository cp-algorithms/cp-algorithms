---
tags:
  - Translated
e_maxx_link: balanced_ternary
---

# Balanced Ternary

!["Setun computer using Balanced Ternary system"](https://earltcampbell.files.wordpress.com/2014/12/setun.jpeg?w=300)

This is a non-standard but still positional **numeral system**. Its feature is that digits can have one of the values `-1`, `0` and `1`.
Nevertheless, its base is still `3` (because there are three possible values). Since it is not convenient to write `-1` as a digit,
we'll use letter `Z` further for this purpose. If you think it is quite a strange system - look at the picture - here is one of the
computers utilizing it.

So here are few first numbers written in balanced ternary:

```nohighlight
    0    0
    1    1
    2    1Z
    3    10
    4    11
    5    1ZZ
    6    1Z0
    7    1Z1
    8    10Z
    9    100
```

This system allows you to write negative values without leading minus sign: you can simply invert digits in any positive number.

```nohighlight
    -1   Z
    -2   Z1
    -3   Z0
    -4   ZZ
    -5   Z11
```

Note that a negative number starts with `Z` and positive with `1`.

## Conversion algorithm

It is easy to represent a given number in **balanced ternary** via temporary representing it in normal ternary number system. When value is
in standard ternary, its digits are either `0` or `1` or `2`. Iterating from the lowest digit we can safely skip any `0`s and `1`s,
however `2` should be turned into `Z` with adding `1` to the next digit. Digits `3` should be turned into `0` on the same terms -
such digits are not present in the number initially but they can be encountered after increasing some `2`s.

**Example 1:** Let us convert `64` to balanced ternary. At first we use normal ternary to rewrite the number:

$$ 64_{10} = 02101_{3} $$

Let us process it from the least significant (rightmost) digit:

- `1`,`0` and `1` are skipped as it is.( Because `0` and `1` are allowed in balanced ternary )
- `2` is turned into `Z` increasing the digit to its left, so we get `1Z101`.

The final result is `1Z101`.

Let us convert it back to the decimal system by adding the weighted positional values:

$$ 1Z101 = 81 \cdot 1 + 27 \cdot (-1) + 9 \cdot 1 + 3 \cdot 0 + 1 \cdot 1 = 64_{10} $$

**Example 2:** Let us convert `237` to balanced ternary. At first we use normal ternary to rewrite the number:

$$ 237_{10} = 22210_{3} $$

Let us process it from the least significant (rightmost) digit:

- `0` and `1` are skipped as it is.( Because `0` and `1` are allowed in balanced ternary )
- `2` is turned into `Z` increasing the digit to its left, so we get `23Z10`.
- `3` is turned into `0` increasing the digit to its left, so we get `30Z10`.
- `3` is turned into `0` increasing the digit to its left( which is by default `0` ), and so we get `100Z10`.

The final result is `100Z10`.

Let us convert it back to the decimal system by adding the weighted positional values:

$$ 100Z10 = 243 \cdot 1 + 81 \cdot 0 + 27 \cdot 0 + 9 \cdot (-1) + 3 \cdot 1 + 1 \cdot 0 = 237_{10} $$

## Practice Problems

* [Topcoder SRM 604, Div1-250](http://community.topcoder.com/stat?c=problem_statement&pm=12917&rd=15837)
