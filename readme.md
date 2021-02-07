# Benchmarks of Modern Web Frameworks

### Go (net/http), Go (fasthttp), Rust (hyper), Rust (actix-web), Drogon (C++), JustJS (node alternative), .NET Core 5, and more to come.

Include docker container configuration configuration, if desired.

See results.txt for my local Docker results.

Note: Primarily these tests only test TEXT and JSON responses at the moment.

## Setup (Mac OS)

* Generally all benchmarks are classified under src/<language>/<framework>/, and can just be configured by cd'ing to that directory and running:
```
./setup.sh (if exists)
./build.sh
./run.sh
```
* If you want to use docker:
    - Install VS Code - Remote - Container extension
    - Open folder in VS Code, and 'open in container' when prompted (it will take a while to build the first time - 20 minutes on 2015 Macbook Pro)
    - Let the container build, and when finished, open terminal
    - `npm install`
    - Start any of the given benchmark servers (each of these is set to run on http://localhost:8080)
    - Tune the parameters in run.js, and then run it: `node run.js` to test any given server below.

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

### Todo: Java

_______________


## Results:

* *NOTE*: these are outdated (run from old machine). See individual 'results.txt' files within the individual framework folders for more recent results.

* See ./results.txt for full results (they are outdated, but still comparable).