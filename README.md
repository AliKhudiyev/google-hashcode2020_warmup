# Google HashCode 2020 Warmup

First find the problem statement (pdf file) in my github repo then check this out!

<hr >

Assuming we have given a maximum score called `max` and the number of pizza types called `types`:

```bash
max types
t[0] t[1] ... t[types-1]
```

Then we make count list of each different `t` to know how many times each unique `t` appears on the input and we get a count list `{ x[0], x[1], ..., x[n] }` corresponding to the list of all different `t` values shown as `{ a[0], a[1], ..., a[n] }`.

Now, it is obvious that score can be rewritten as follows:

```bash
score = a[0]x[0] + a[1]x[1] + ... + a[n]x[n]
```

The mathematical description of the problem is the following:

```bash
a[0]x[0] + a[1]x[1] + ... + a[n]x[n] <= max

0 <= x[0] <= m[0]
0 <= x[1] <= m[1]
...
0 <= x[n] <= m[n]
```

**Statement:** Given the conditions above find the maximum of `score`.

Since all `a` values are given we have to find such `x` values to maximize the `score`.

## How to run

After downloading the project from [here](#) open up a terminal from the project folder and enter:

```bash
./main [path/to/input] [path/to/output]
```

- [path/to/input] is a location of an input file (provided in the directory called **in**, i.e. **in/a_example.in**)

- [path/to/output] is a location of an output file to be saved (i.e. **out/a_example.out**)

### Statistics

|    Input   |   Score   |  Time  | Lost Point |
|-----------:|:---------:|:-------|:-----------|
|a_example   | 16        | 0.3 ms | 0          |
|b_small     | 98        | 0.32 ms| 2          |
|c_medium    | 4496      | 0.35 ms| 4          |
|d_big       | 999999989 | 2.3 ms | < 11       |
|e_quite_big | 504999988 | 6.7 ms | < 12       |
