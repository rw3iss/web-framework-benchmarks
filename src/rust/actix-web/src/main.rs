use actix_files as fs;
use actix_utils::mpsc;
use actix_session::{CookieSession, Session};
use actix_web::http::{header, Method, StatusCode};
use actix_web::{
    error, get, guard, middleware, web, App, Error, HttpRequest, HttpResponse, HttpServer, Result, Responder
};
use std::{env, io};
use serde::Serialize;

#[derive(Serialize)]
struct User<'a> {
    id: i16,
    username: &'a str,
    email: &'a str,
}

/// 404 handler
async fn p404() -> Result<fs::NamedFile> {
    Ok(fs::NamedFile::open("static/404.html")?.set_status_code(StatusCode::NOT_FOUND))
}

#[get("/json")]
async fn json(_session: Session, _req: HttpRequest) -> HttpResponse {
    let user = User { id: 1, username: "username", email: "email@email.com" };

    HttpResponse::Ok().json(user)
}

/// simple index handler
#[get("/welcome")]
async fn welcome(session: Session, req: HttpRequest) -> Result<HttpResponse> {
    println!("{:?}", req);

    // session
    let mut counter = 1;
    if let Some(count) = session.get::<i32>("counter")? {
        println!("SESSION value: {}", count);
        counter = count + 1;
    }

    // set counter to session
    session.set("counter", counter)?;

    // response
    Ok(HttpResponse::build(StatusCode::OK)
        .content_type("text/html; charset=utf-8")
        .body(include_str!("../static/welcome.html")))
}

#[actix_web::main]
async fn main() -> io::Result<()> {
    env::set_var("RUST_LOG", "actix_web=debug,actix_server=info");
    //env_logger::init();

    HttpServer::new(|| {
        App::new()
            // cookie session middleware
            //.wrap(CookieSession::signed(&[0; 32]).secure(false))
            // enable logger - always register actix-web Logger middleware last
            //.wrap(middleware::Logger::default())
            // register simple route, handle all methods
            .service(json)

            .service(welcome)

            .service(web::resource("/").route(web::get().to(|req: HttpRequest| {
                println!("{:?}", req);
                HttpResponse::Found()
                    .header(header::LOCATION, "static/welcome.html")
                    .finish()
            })))
            // default
            .default_service(
                // 404 for GET request
                web::resource("")
                    .route(web::get().to(p404))
                    // all requests that are not `GET`
                    .route(
                        web::route()
                            .guard(guard::Not(guard::Get()))
                            .to(HttpResponse::MethodNotAllowed),
                    ),
            )
    })
    .bind("127.0.0.1:8080")? 
    .run()
    .await
}