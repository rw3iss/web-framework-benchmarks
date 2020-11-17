package main

import (
        "encoding/json"
        "fmt"

        "github.com/valyala/fasthttp"
)

type User struct {
        Username string
        Email    string
}

func main() {
        fmt.Printf("Starting server at port 8080\n")
        //h := fastHttpHandler
        h := fasthttp.CompressHandler(fastHttpHandler)
        fasthttp.ListenAndServe(":8080", h)
}

func fastHttpHandler(ctx *fasthttp.RequestCtx) {
        switch string(ctx.Path()) {
        case "/json":
                jsonTestHandler(ctx)
        default:
                fmt.Fprint(ctx, "Hello World!")
        }
}

func jsonTestHandler(ctx *fasthttp.RequestCtx) {
        var user User
        user.Username = "username"
        user.Email = "email@email.com"

        ctx.Response.Header.Set("Content-Type", "application/json")

        json.NewEncoder(ctx).Encode(user)
}