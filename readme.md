# Benchmarks of Modern Web Frameworks

This repository houses a myriad of different web technologies for local benchmarking of simple requests (just TEXT and JSON for now). The included technologies/frameworks are:

## Tests:
- Go (net/http)
- Go (fasthttp)
- Rust (hyper)
- Rust (actix-web)
- Drogon (C++)
- JustJS (faster node alternative)
- .NET Core 5
- ~~Java (TODO)~~

Each individual framework folders has a 'results.txt' file of the latest results.

Note: This repository ncludes Docker container configuration configuration, but not necessary.

## Setup:

Generally all benchmarks are classified under src/\<language>/\<framework>/, and can just be configured by cd'ing to that directory and running:
```
./setup.sh (if exists)
./build.sh
./run.sh
```

## Individual Framework Setup / Remarks:

### Go:
```
cd src/go && go run server.go
```

### Rust:
> Hyper:
```
cd src/rust/hyper && ./build.sh
./run.sh
```
> Actix-web:
```
cd src/rust/actix-web && ./build.sh
./run.sh
```
> std library:
```
cd src/rust/std && ./build.sh
./run.sh
```

### Drogon:
```
cd src/drogon && ./setup.sh && ./build.sh
./run.sh
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

### Java
(Todo)

<br/>


## Using Docker:
If you want to use Docker (this may be outdated, but mostly working):
- Install VS Code - Remote - Container extension
- Open folder in VS Code, and 'open in container' when prompted (it will take a while to build the first time - 20 minutes on 2015 Macbook Pro)
- Let the container build, and when finished, open terminal
- `npm install`
- Start any of the given benchmark servers (each of these is set to run on http://localhost:8080)
- Tune the parameters in run.js, and then run it: `node run.js` to test any given server below.

_______________


## Results:

* See individual 'results.txt' files within the individual framework folders for most recent results.
* Spoiler: Rust (actix-web and hyper) and Go (fasthttp) are the fastest by far, almost equally.
