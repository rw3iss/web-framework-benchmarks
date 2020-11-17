extern crate may;
use may_minihttp::{BodyWriter, HttpServer, HttpService, Request, Response};
use std::io;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct Person {
    name: String,
    username: String,
}

#[derive(Clone)]
struct HelloJson;

impl HttpService for HelloJson {
    fn call(&mut self, req: Request, rsp: &mut Response) -> io::Result<()> {
        match req.path() {
            "/json" => {
                let p = Person {
                    name: "Ryan".to_string(),
                    username: "rw3iss".to_string(),
                };

                // //rsp.header("Content-Type: application/json");
                serde_json::to_writer(BodyWriter(rsp.body_mut()), &p)?;
            },
            _ => {
                rsp.status_code("404", "Not Found");
            }
        }

        Ok(())
    }
}

fn main() {
    let server = HttpServer(HelloJson).start("127.0.0.1:8080").unwrap();
    server.wait();

    //let cpus = num_cpus::get();
    //let db_url = "postgres://benchmarkdbuser:benchmarkdbpass@127.0.0.1/hello_world";
    // let http_server = HttpServer{};
    // let server = http_server.start("0.0.0.0:8080").unwrap();
    // server.join().unwrap();
}