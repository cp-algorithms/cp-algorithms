<!--?title Balanced Ternary-->
#Balanced Ternary

<img src="./img/balanced-ternary.jpg" alt="Setun computer using Balanced Ternary system" align="right" width="200"/>

This is a non-standard but still positional **numeral system**. It's feature is that digits can have one of values `-1`, `0` and `1`.
Nevertheless its base is still `3` (because there are three possible values). Since it is not convenient to write `-1` as a digit
we'll use letter `Z` further for this purpose. If you think it is quite strange system - look at the picture - here is one of the
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

This system allows to write negative values without leading minus sign: you can simply invert digits in any positive number

```nohighlight
    -1   Z
    -2   Z1
    -3   Z0
    -4   ZZ
    -5   Z11
```

Note that negative number starts with `Z` and positive with `1`.

###Conversion algorithm

It is easy to convert represent number in **balanced ternary** via temporary representing it as normal ternary. When value is
in standard ternary, its digits are either `0` or `1` or `2`. Iterating from the lowest digit we can safely skip any `0`s and `1`s,
however `2` should be turned into `Z` with adding `1` to the next digit. Digits `3` should be turned into `0` on the same terms -
such digits are not present in the number initially but they can be encountered after increasing some `2`s.

**Example:** let us convert `64` to balanced ternary. At first we use normal ternary to rewrite the number:

$$ 64 = 02201_{3} $$

Let us process it from the least significant (rightmost) digit:

- `1` is skipped as is, `0` at the next position too;
- `2` is turned into `Z` increasing the following digit, so we get `03Z01` (temporarily);
- `3` is turned into `0` increasing the following digit (which, luckily, was `0`).

So the result is `10Z01`.

###Relevant problems

[Topcoder SRM 604, Div1-250](http://community.topcoder.com/stat?c=problem_statement&pm=12917&rd=15837)
