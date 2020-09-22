# Benchmark Between Go (v1.15.2) vs. .NET Core 5.0 (RC)

## Setup (Mac OS)

### Go:
```
brew update
brew install golang
go get github.com/go-sql-driver/mysql
go run server.go
```

### .NET Core 5:
```
Install .pkg from: https://dotnet.microsoft.com/download/dotnet/5.0
dotnet new webapi
dotnet add package MySqlConnector
dotnet publish
dotnet bin/Debug/net5.0/benchmark.dll
```

_______________

## Test: 
Reading and Writing to SQL Database, with Apache Benchmark.

### Write:
```
ab -k -l -p payload.json -T application/json -c 50 -n 10000 http://localhost:5000/benchmark
```

### Read:
```
ab -k -l -c 50 -n 10000 http://localhost:5000/benchmark
```

### Read JSON Only (doesn't touch DB):
```
ab -k -l -c 50 -n 10000 http://localhost:5000/benchmark/json
```

### JSON file for POST payload (not used by code):
```
{ 
    "username": "username", 
    "email": "email@email.com" 
}
```

### Database Schema (for DB tests):
```
create table users ( id INT PRIMARY KEY AUTO_INCREMENT, username VARCHAR(50) NOT NULL, email VARCHAR(255) );
```
_______________


# Results (see bottom for summary):

## Platform

2015 13" MacBook Pro - i7 3.1Ghz, 16GB Ram

## 10k requests, 50 concurrent:
_______________

#### Go (POST - Db Write):
```
Concurrency Level:      50
Time taken for tests:   1.338 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    10000
Total transferred:      1358894 bytes
Total body sent:        2330000
HTML transferred:       48894 bytes
Requests per second:    7475.72 [#/sec] (mean)
Time per request:       6.688 [ms] (mean)
Time per request:       0.134 [ms] (mean, across all concurrent requests)
Transfer rate:          992.06 [Kbytes/sec] received
                        1701.02 kb/s sent
                        2693.08 kb/s total

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       2
Processing:     1    7   4.0      6      52
Waiting:        0    7   4.0      5      52
Total:          1    7   4.0      6      52

Percentage of the requests served within a certain time (ms)
  50%      6
  66%      7
  75%      8
  80%      9
  90%     12
  95%     15
  98%     18
  99%     21
 100%     52 (longest request)
```

#### Go (GET - Db Read):
```
Concurrency Level:      50
Time taken for tests:   1.183 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    10000
Total transferred:      1890000 bytes
HTML transferred:       570000 bytes
Requests per second:    8454.86 [#/sec] (mean)
Time per request:       5.914 [ms] (mean)
Time per request:       0.118 [ms] (mean, across all concurrent requests)
Transfer rate:          1560.52 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       2
Processing:     1    6   3.8      5     105
Waiting:        0    6   3.8      5     105
Total:          1    6   3.8      5     105

Percentage of the requests served within a certain time (ms)
  50%      5
  66%      6
  75%      7
  80%      8
  90%     10
  95%     13
  98%     16
  99%     18
 100%    105 (longest request)
```

#### Go (GET - JSON Only):
```
Concurrency Level:      50
Time taken for tests:   0.286 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    10000
Total transferred:      1890000 bytes
HTML transferred:       570000 bytes
Requests per second:    34946.10 [#/sec] (mean)
Time per request:       1.431 [ms] (mean)
Time per request:       0.029 [ms] (mean, across all concurrent requests)
Transfer rate:          6450.01 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.1      0       2
Processing:     0    1   1.2      1      10
Waiting:        0    1   1.2      1      10
Total:          0    1   1.2      1      10

Percentage of the requests served within a certain time (ms)
  50%      1
  66%      1
  75%      2
  80%      2
  90%      3
  95%      4
  98%      6
  99%      6
 100%     10 (longest request)
 ```

-----------------------------


#### .NET Core 5.0 RC (production build) (POST - Db Write):
```
Concurrency Level:      50
Time taken for tests:   13.472 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1428894 bytes
Total body sent:        2330000
HTML transferred:       38894 bytes
Requests per second:    742.30 [#/sec] (mean)
Time per request:       67.358 [ms] (mean)
Time per request:       1.347 [ms] (mean, across all concurrent requests)
Transfer rate:          103.58 [Kbytes/sec] received
                        168.90 kb/s sent
                        272.48 kb/s total

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   18  62.7     16    2763
Processing:     4   47 137.2     33    2052
Waiting:        3   34 106.1     24    2035
Total:         10   65 151.4     49    2791

Percentage of the requests served within a certain time (ms)
  50%     49
  66%     61
  75%     67
  80%     71
  90%     80
  95%     88
  98%     99
  99%    552
 100%   2791 (longest request)
```

#### .NET Core 5.0 RC (production build) (GET - Db Read):
```
Concurrency Level:      50
Time taken for tests:   8.528 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1950000 bytes
HTML transferred:       560000 bytes
Requests per second:    1172.63 [#/sec] (mean)
Time per request:       42.639 [ms] (mean)
Time per request:       0.853 [ms] (mean, across all concurrent requests)
Transfer rate:          223.30 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   13  11.0     13     504
Processing:     2   29  35.6     25     532
Waiting:        0   19  26.7     17     506
Total:          9   42  37.5     38     558

Percentage of the requests served within a certain time (ms)
  50%     38
  66%     44
  75%     47
  80%     49
  90%     56
  95%     62
  98%     69
  99%     87
 100%    558 (longest request)
```

#### .NET Core 5.0 RC (production build) (GET - JSON Only):
```
Concurrency Level:      50
Time taken for tests:   6.718 seconds
Complete requests:      10000
Failed requests:        0
Keep-Alive requests:    0
Total transferred:      1850000 bytes
HTML transferred:       460000 bytes
Requests per second:    1488.64 [#/sec] (mean)
Time per request:       33.588 [ms] (mean)
Time per request:       0.672 [ms] (mean, across all concurrent requests)
Transfer rate:          268.94 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   13  34.1     10     561
Processing:     1   20  36.3     16     568
Waiting:        0   14  30.0     10     562
Total:          6   33  49.9     26     587

Percentage of the requests served within a certain time (ms)
  50%     26
  66%     30
  75%     34
  80%     37
  90%     44
  95%     50
  98%     79
  99%    433
 100%    587 (longest request)
```

_______________

## Summary:


### Go (POST - Db Write):
Requests per second:    7475.72 [#/sec] (mean)

### Go (GET - Db Read):
Requests per second:    8454.86 [#/sec] (mean)

### Go (GET - JSON Only):
Requests per second:    34946.10 [#/sec] (mean)

### .NET Core 5.0 RC (production build) (POST - Db Write):
Requests per second:    742.30 [#/sec] (mean)

### .NET Core 5.0 RC (production build) (GET - Db Read):
Requests per second:    1172.63 [#/sec] (mean)

### .NET Core 5.0 RC (production build) (GET - JSON Only):
Requests per second:    1488.64 [#/sec] (mean)


