# Benchmark Between Go (v1.15.2) vs. .NET Core 5.0 (RC) vs. Rust 1.42 (actix-web v3)

See results.txt for my local Docker results.

Note: Primarily these tests only test JSON responses at the moment.

## Setup (Mac OS)

* Install VS Code - Remote - Container extension
* Open folder in VS Code, and 'open in container' when prompted (it will take a while to build the first time - 20 minutes on 2015 Macbook Pro)
* Let the container build, and when finished, open terminal
* `npm install`
* Start any of the given benchmark servers (each of these is set to run on http://localhost:8080)
* Tune the parameters in run.js, and then run it: `node run.js` to test any given server below.


### Go:
```
cd src/go
go get github.com/go-sql-driver/mysql
go run server.go
```

### Rust:
```
cd src/rust/hyper
cargo run --release
```

### Drogon:
```
cd src/drogon/benchmark/build
cmake ..
make
./benchmark
```

### JustJS:
```
Todo: see JustJS repo for installation/docker setup.
cd src/justjs/benchmark
npm start
```

### .NET Core 5  (TODO: needs installation fix / not tested in Docker yet)
```
Install .pkg from: https://dotnet.microsoft.com/download/dotnet/5.0
dotnet new webapi
dotnet add package MySqlConnector
dotnet publish
dotnet bin/Debug/net5.0/benchmark.dll
```

### Todo: Java

_______________


## Docker Container Results (Early 2015 Macbook Pro 13" 3.1Ghz):

* (See results.txt)


## Go (with net/http):
------------------
```
c=50
 { timeTaken: 0.53, rps: 20559.15, tps: 0.05, rate: 3834.76 }
 { timeTaken: 0.44, rps: 23875.14, tps: 0.04, rate: 4453.27 }
 { timeTaken: 0.5, rps: 20635.87, tps: 0.05, rate: 3808.77 }
 { timeTaken: 0.54, rps: 22003.53, tps: 0.05, rate: 4061.2 }
 { timeTaken: 0.51, rps: 22428.85, tps: 0.05, rate: 4139.7 }
 { timeTaken: 0.52, rps: 19987.12, tps: 0.05, rate: 3689.0 }

 { timeTaken: 0.36, rps: 28235.43, tps: 0.04, rate: 5459.59 }
 { timeTaken: 0.5, rps: 21157.28, tps: 0.05, rate: 4090.96 }
 { timeTaken: 0.57, rps: 19839.28, tps: 0.06, rate: 3836.11 }
 { timeTaken: 0.58, rps: 18418.84, tps: 0.06, rate: 3561.45 }
 { timeTaken: 0.37, rps: 27236.09, tps: 0.04, rate: 5266.35 }

c=250
 { timeTaken: 0.42, rps: 26508.69, tps: 0.04, rate: 4892.72 }
 { timeTaken: 0.40, rps: 26534.68, tps: 0.04, rate: 4897.51 }
 { timeTaken: 0.45, rps: 23422.13, tps: 0.04, rate: 4323.03 }
 { timeTaken: 0.45, rps: 22661.16, tps: 0.04, rate: 4182.58 }

c=1000
 { timeTaken: 0.46, rps: 24555.12, tps: 0.05, rate: 4532.15 }
 { timeTaken: 0.38, rps: 26834.81, tps: 0.04, rate: 4952.91 }
 { timeTaken: 0.42, rps: 25001.62, tps: 0.04, rate: 4614.56 }
 { timeTaken: 0.49, rps: 24320.42, tps: 0.05, rate: 4488.83 }

 { timeTaken: 0.32, rps: 32115.00, tps: 0.03, rate: 6209.74 }
 { timeTaken: 0.49, rps: 24966.65, tps: 0.05, rate: 4827.53 }
 { timeTaken: 0.48, rps: 21606.65, tps: 0.05, rate: 4177.85 }
 { timeTaken: 0.42, rps: 26172.82, tps: 0.04, rate: 5060.76 }

 { timeTaken: 0.4, rps: 26479.92, tps: 0.04, rate: 4939.13 }
```

## Go (with fasthttp):
```
c=50:
*{ timeTaken: 0.25, rps: 41727.84, tps: 0.02, rate: 8149.97 }
 { timeTaken: 0.26, rps: 38826.48, tps: 0.03, rate: 7583.3 }
 { timeTaken: 0.4, rps: 28761.36, tps: 0.04, rate: 5617.45 }
 { timeTaken: 0.39, rps: 28690.93, tps: 0.04, rate: 5603.7 }

 { timeTaken: 0.32, rps: 33324.92, tps: 0.03, rate: 6508.77 }
 { timeTaken: 0.28, rps: 35946.28, tps: 0.03, rate: 7020.76 }
 { timeTaken: 0.34, rps: 32216.69, tps: 0.03, rate: 6292.32 }
 { timeTaken: 0.38, rps: 28769.44, tps: 0.04, rate: 5619.03 }

c=100:
 { timeTaken: 0.26, rps: 39815.31, tps: 0.03, rate: 7776.43 }
 { timeTaken: 0.29, rps: 35718.27, tps: 0.03, rate: 6976.22 }
 { timeTaken: 0.39, rps: 30300.61, tps: 0.04, rate: 5918.09 }
 { timeTaken: 0.31, rps: 32984.34, tps: 0.03, rate: 6442.25 }

 { timeTaken: 0.25, rps: 41479.45, tps: 0.02, rate: 8101.45 }
 { timeTaken: 0.3, rps: 37431.63, tps: 0.03, rate: 7310.86 }
 { timeTaken: 0.35, rps: 34139.64, tps: 0.03, rate: 6667.9 }
 { timeTaken: 0.34, rps: 32041.14, tps: 0.03, rate: 6258.04 }

c=1000:
 { timeTaken: 0.3, rps: 34375.15, tps: 0.03, rate: 6713.9 }
 { timeTaken: 0.33, rps: 33055.04, tps: 0.03, rate: 6456.06 }
 { timeTaken: 0.4, rps: 30125.91, tps: 0.04, rate: 5883.96 }
 { timeTaken: 0.42, rps: 28797.73, tps: 0.04, rate: 5624.56 }
```


------------------
## Rust (hyper):
```
c=50
*{ timeTaken: 0.23, rps: 45311.09, tps: 0.02, rate: 5973.63 }
 { timeTaken: 0.26, rps: 40082.62, tps: 0.03, rate: 5284.33 }
 { timeTaken: 0.69, rps: 17068.49, tps: 0.07, rate: 2250.24 }
 { timeTaken: 0.34, rps: 34189.97, tps: 0.03, rate: 4507.47 }

 { timeTaken: 0.42, rps: 29600.85, tps: 0.04, rate: 3902.46 }
 { timeTaken: 0.46, rps: 23968.67, tps: 0.05, rate: 3159.93 }
 { timeTaken: 0.29, rps: 38945.22, tps: 0.03, rate: 5134.38 }
 { timeTaken: 0.34, rps: 32399.25, tps: 0.03, rate: 4271.39 }

 { timeTaken: 0.27, rps: 39160.52, tps: 0.03, rate: 5162.76 }
 { timeTaken: 0.31, rps: 38098.53, tps: 0.03, rate: 5022.76 }
 { timeTaken: 0.29, rps: 39106.03, tps: 0.03, rate: 5155.58 }
 { timeTaken: 0.32, rps: 34026.22, tps: 0.03, rate: 4485.88 }

c=100
 { timeTaken: 0.48, rps: 22664.93, tps: 0.05, rate: 2988.05 }
 { timeTaken: 0.34, rps: 30092.82, tps: 0.03, rate: 3967.31 }
 { timeTaken: 0.37, rps: 30210.51, tps: 0.04, rate: 3982.83 }
 { timeTaken: 0.38, rps: 27448.9, tps: 0.04, rate: 3618.75 }

c=250
  { timeTaken: 0.45, rps: 23237.99, tps: 0.05, rate: 3063.6 }
  { timeTaken: 0.58, rps: 20908.98, tps: 0.06, rate: 2756.55 }
  { timeTaken: 0.45, rps: 23318.29, tps: 0.05, rate: 3074.19 }
  { timeTaken: 0.42, rps: 25143.78, tps: 0.04, rate: 3314.85 }

c=1000
 { timeTaken: 0.51, rps: 21968.91, tps: 0.05, rate: 2896.29 }
 { timeTaken: 0.49, rps: 23011.21, tps: 0.05, rate: 3033.71 }
 { timeTaken: 0.5, rps: 22180.29, tps: 0.05, rate: 2924.16 }
 { timeTaken: 0.43, rps: 23448.48, tps: 0.04, rate: 3091.35 }

 { timeTaken: 0.31, rps: 33472.31, tps: 0.03, rate: 4412.85 }
 { timeTaken: 0.45, rps: 24219.5, tps: 0.05, rate: 3193 }
 { timeTaken: 0.46, rps: 23917.19, tps: 0.05, rate: 3153.14 }
 { timeTaken: 0.38, rps: 26239.31, tps: 0.04, rate: 3459.28 }
```

## Rust (actix-web):
------------------
```
c=50
 { timeTaken: 0.43, rps: 24903.15, tps: 0.04, rate: 4572.06 }
 { timeTaken: 0.45, rps: 24938.99, tps: 0.05, rate: 4578.64 }
 { timeTaken: 0.31, rps: 32072.63, tps: 0.03, rate: 5888.33 }
 { timeTaken: 0.35, rps: 29056.29, tps: 0.04, rate: 5334.55 }

c=1000
 { timeTaken: 0.48, rps: 22006.46, tps: 0.05, rate: 4040.25 }
 { timeTaken: 0.49, rps: 25289.13, tps: 0.05, rate: 4642.93 }
 { timeTaken: 0.44, rps: 24463.7, tps: 0.04, rate: 4491.38 }
 { timeTaken: 0.51, rps: 22980.34, tps: 0.05, rate: 4219.05 }
```


## JustJS:
------------------
```
c=50
 { timeTaken: 2.95, rps: 3792.57, tps: 0.3, rate: 618.52 }

c=1000
 { timeTaken: 2.33, rps: 4410.32, tps: 0.23, rate: 719.26 }
```

## Drogon:
------------------
```
c=50
*{ timeTaken: 0.27, rps: 37207.2, tps: 0.03, rate: 7485.04 }
 { timeTaken: 0.4, rps: 27064.39, tps: 0.04, rate: 5444.59 }
 { timeTaken: 0.41, rps: 25841.77, tps: 0.04, rate: 5198.64 }
 { timeTaken: 0.39, rps: 27169.53, tps: 0.04, rate: 5465.74 }

 { timeTaken: 0.55, rps: 25478.02, tps: 0.06, rate: 5125.46 }
 { timeTaken: 0.31, rps: 32623.34, tps: 0.03, rate: 6562.9 }
 { timeTaken: 0.5, rps: 23840.75, tps: 0.05, rate: 4796.09 }
 { timeTaken: 0.31, rps: 32949.84, tps: 0.03, rate: 6628.58 }

 { timeTaken: 0.32, rps: 31528.42, tps: 0.03, rate: 6342.63 }
 { timeTaken: 0.46, rps: 25469.61, tps: 0.05, rate: 5123.77 }
 { timeTaken: 0.38, rps: 29496.24, tps: 0.04, rate: 5933.81 }
 { timeTaken: 0.32, rps: 32979.32, tps: 0.03, rate: 6634.51 }

c=1000
 { timeTaken: 0.44, rps: 23422.02, tps: 0.04, rate: 4711.85 }
 { timeTaken: 0.41, rps: 25231.58, tps: 0.04, rate: 5075.89 }
 { timeTaken: 0.39, rps: 26147.84, tps: 0.04, rate: 5260.21 }
 { timeTaken: 0.49, rps: 23160.67, tps: 0.05, rate: 4659.28 }

 { timeTaken: 0.56, rps: 18952.2, tps: 0.06, rate: 3812.65 }
 { timeTaken: 0.43, rps: 23968.84, tps: 0.04, rate: 4821.86 }
 { timeTaken: 0.49, rps: 21537.82, tps: 0.05, rate: 4332.8 }
 { timeTaken: 0.48, rps: 22263.87, tps: 0.05, rate: 4478.87 }
```
