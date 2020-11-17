use crate::{Context, Response};
use hyper::StatusCode;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize)]
struct Person {
    name: String,
    username: String,
}

pub async fn test_handler(ctx: Context) -> String {
    format!("test called, state_thing was: {}", ctx.state.state_thing)
}

pub async fn json_handler(ctx: Context) -> String {
    let p = Person {
        name: "Ryan".to_string(),
        username: "rw3iss".to_string(),
    };

    // Serialize it to a JSON string.
    let j = serde_json::to_string(&p).unwrap();
    format!("{}", j)
}

#[derive(Deserialize)]
struct SendRequest {
    name: String,
    active: bool,
}

pub async fn send_handler(mut ctx: Context) -> Response {
    let body: SendRequest = match ctx.body_json().await {
        Ok(v) => v,
        Err(e) => {
            return hyper::Response::builder()
                .status(StatusCode::BAD_REQUEST)
                .body(format!("could not parse JSON: {}", e).into())
                .unwrap()
        }
    };

    Response::new(
        format!(
            "send called with name: {} and active: {}",
            body.name, body.active
        )
        .into(),
    )
}

pub async fn param_handler(ctx: Context) -> String {
    let param = match ctx.params.find("some_param") {
        Some(v) => v,
        None => "empty",
    };
    format!("param called, param was: {}", param)
}