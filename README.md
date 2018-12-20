# CFLP
Capacitated Facility Location Problem

## Introduction

Suppose there are n facilities and m customers. We wish
to choose:
1. which of the n facilities to open
2. the assignment of customers to facilities

**The objective is to minimize the sum of the opening cost
and the assignment cost.**

**The total demand assigned to a facility must not exceed
its capacity.**

## Problem Instance

```bash
10 50             #10个facility，50个customer. n = 10, m = 50

258 366           #这10行给出了每个facility的capacity和open cost
128 314
296 504
225 504
310 580
373 415
329 456
179 549
114 310
321 316
                  #每个customer的demand
   49.   29.   23.   40.   18.   17.   48.   13.   15.   31.
   16.   31.   14.   44.   23.   39.   33.   45.   40.   43.
   38.   26.   47.   34.   24.   32.   28.   26.   20.   13.
   27.   22.   14.   42.   31.   37.   45.   20.   38.   21.
   25.   13.   19.   42.   10.   21.   37.   27.   17.   49.

                  #接下来有n * m个数据
                  #与行、列无关
                  #每m个数据对应m个customer分配给1个facility的assigncost
  260.  239.  418.  557.  346.  161.  288.  568.  379.  392.
  672.  268.  122.  295.  344.  143.  393.   29.  656.  654.
  235.  329.  640.  517.  329.  524.  318.  516.   79.  414.
  458.  758.   28.  167.  504.  502.  475.  226.   94.  422.
  303.  139.  362.  519.  494.   88.  468.   72.  370.   68.
```

## Result
Detailed solution for each problem instance in 3 lines:

```bash
1234                      #总的cost(每个facility的open cost + 每个customer的assigment cost)
0 1 0 1 0 0 1 1 0 1       #facility最终的状态，1 for open，0 for close
1 3 6 7 9...              #每个customer被分配给哪个facility
                          #customer 0 to facility 1, customer 1 to facility 3
```
