# Benchmark Between Go (v1.15.2) vs. .NET Core 5.0 (RC)

## Setup

### Go:
```
brew update
brew install golang
go get github.com/go-sql-driver/mysql
```

### .NET Core 5:
```
dotnet new webapi
dotnet add package MySqlConnector
dotnet publish
dotnet bin/Debug/net5.0/benchmark.dll
```

_______________

## Test: 
Reading and Writing to SQL Database, with Apache Benchmark.

### Write:
ab -k -l -p payload.json -T application/json -c 50 -n 10000 http://localhost:8081/benchmark

### Read:
ab -k -l -c 50 -n 10000 http://localhost:8081/benchmark

### JSON file for POST payload (not used by code):
{ 
    "username": "username", 
    "email": "email@email.com" 
}
_______________


# Results (see bottom for summary):

## Platform

2015 13" MacBook Pro - i7 3.1Ghz, 16GB Ram

## 10k requests, 50 concurrent:
_______________

#### Go (POST - Db Write):
```
Concurrency Level:      50
Time taken for tests:   1.590 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    10000
Total transferred:      1358894 bytes
Total body sent:        2330000
HTML transferred:       48894 bytes
Requests per second:    6290.48 [#/sec] (mean)
Time per request:       7.949 [ms] (mean)
Time per request:       0.159 [ms] (mean, across all concurrent requests)
Transfer rate:          834.78 [Kbytes/sec] received
                        1431.33 kb/s sent
                        2266.11 kb/s total

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.2      0       4
Processing:     1    8   5.8      6      63
Waiting:        0    8   5.8      6      63
Total:          1    8   5.8      6      63

Percentage of the requests served within a certain time (ms)
  50%      6
  66%      8
  75%      9
  80%     11
  90%     15
  95%     20
  98%     26
  99%     32
 100%     63 (longest request)
```

#### Go (GET - Db Read):
```
Concurrency Level:      50
Time taken for tests:   1.317 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    10000
Total transferred:      1890000 bytes
HTML transferred:       570000 bytes
Requests per second:    7592.43 [#/sec] (mean)
Time per request:       6.586 [ms] (mean)
Time per request:       0.132 [ms] (mean, across all concurrent requests)
Transfer rate:          1401.34 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       2
Processing:     1    7   4.7      5      78
Waiting:        0    7   4.7      5      78
Total:          1    7   4.7      5      78

Percentage of the requests served within a certain time (ms)
  50%      5
  66%      6
  75%      7
  80%      8
  90%     13
  95%     17
  98%     20
  99%     24
 100%     78 (longest request)
```

-----------------------------


#### .NET Core 5.0 (POST - Db Write) (development build):
```
Concurrency Level:      50
Time taken for tests:   17.454 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1428894 bytes
Total body sent:        2330000
HTML transferred:       38894 bytes
Requests per second:    572.93 [#/sec] (mean)
Time per request:       87.270 [ms] (mean)
Time per request:       1.745 [ms] (mean, across all concurrent requests)
Transfer rate:          79.95 [Kbytes/sec] received
                        130.36 kb/s sent
                        210.31 kb/s total

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   25  19.0     25     289
Processing:     5   59  46.3     51     644
Waiting:        2   44  44.4     37     644
Total:          9   84  49.6     79     646

Percentage of the requests served within a certain time (ms)
  50%     79
  66%     91
  75%     99
  80%    105
  90%    122
  95%    138
  98%    164
  99%    316
 100%    646 (longest request)
````

#### .NET Core 5.0 (GET - Db Read) (development build):
```
Concurrency Level:      50
Time taken for tests:   8.932 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1950000 bytes
HTML transferred:       560000 bytes
Requests per second:    1119.60 [#/sec] (mean)
Time per request:       44.659 [ms] (mean)
Time per request:       0.893 [ms] (mean, across all concurrent requests)
Transfer rate:          213.21 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   15  12.5     13     193
Processing:     3   29  17.9     25     205
Waiting:        1   20  15.2     16     194
Total:         11   44  22.8     40     211

Percentage of the requests served within a certain time (ms)
  50%     40
  66%     49
  75%     54
  80%     57
  90%     68
  95%     77
  98%     87
  99%    103
 100%    211 (longest request)
```

-----------------------------


#### .NET Core 5.0 (POST - Db Write) (production build):
```
Concurrency Level:      50
Time taken for tests:   15.164 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1428894 bytes
Total body sent:        2330000
HTML transferred:       38894 bytes
Requests per second:    659.44 [#/sec] (mean)
Time per request:       75.822 [ms] (mean)
Time per request:       1.516 [ms] (mean, across all concurrent requests)
Transfer rate:          92.02 [Kbytes/sec] received
                        150.05 kb/s sent
                        242.07 kb/s total

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   22  27.3     21     415
Processing:     3   51  50.4     43     640
Waiting:        2   36  48.9     30     640
Total:         11   73  58.4     66     641

Percentage of the requests served within a certain time (ms)
  50%     66
  66%     74
  75%     80
  80%     85
  90%     99
  95%    120
  98%    175
  99%    459
 100%    641 (longest request)
```

#### .NET Core 5.0 (GET - Db Read) (production build):
```
Concurrency Level:      50
Time taken for tests:   15.296 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1950000 bytes
HTML transferred:       560000 bytes
Requests per second:    653.76 [#/sec] (mean)
Time per request:       76.481 [ms] (mean)
Time per request:       1.530 [ms] (mean, across all concurrent requests)
Transfer rate:          124.50 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        1   29 142.3     17    2439
Processing:     1   46 115.0     31    2445
Waiting:        1   29  73.1     21    2444
Total:         21   75 182.1     50    2463

Percentage of the requests served within a certain time (ms)
  50%     50
  66%     58
  75%     64
  80%     69
  90%     85
  95%    113
  98%    235
  99%    552
 100%   2463 (longest request)
```


_______________

## Summary:


### Go (POST - Db Write):
Requests per second:    6290.48 [#/sec] (mean)

### Go (GET - Db Read):
Requests per second:    7592.43 [#/sec] (mean)

### .NET Core 5.0 (POST - Db Write) (development build):
Requests per second:    572.93 [#/sec] (mean)

### .NET Core 5.0 (GET - Db Read) (development build):
Requests per second:    1119.60 [#/sec] (mean)

### .NET Core 5.0 (POST - Db Write) (production build):
Requests per second:    659.44 [#/sec] (mean)

### .NET Core 5.0 (GET - Db Read) (production build):
Requests per second:    653.76 [#/sec] (mean)

