
# What This Is:
    
A small basic web application library/example written for the [JustJS](https://github.com/just-js/just) V8 JavaScript technology (basically a much faster NodeJS alternative).
    
# Note
    
This library is very primitive and not intended for usage yet, but basically works.
    
# How to use:

Copy this repository into a folder within the above JustJS repository's /examples folder.

Navigate to the folder and 'npm start' to start the existing server.

Edit the src/server.js code (and whatever src/lib code) to suit your application's needs (see below for development).

     
# To develop locally:

JustJS must be used with linux (or Docker), see repo above. To use this with the JustJS Docker build, add this to the JustJS .devcontainer/Dockerfile, in the middle somewhere, and rebuild the container:

    ## NODE + ESBUILD REQUIREMENTS ###
    RUN apt-get install -y curl nodejs
    RUN curl -sL https://deb.nodesource.com/setup_15.x | sudo -E bash -
    RUN sudo npm install nodemon esbuild -g
    ##################

Then enter the container, and in the terminal install the app preqrequsities:

    npm install

Then start the nodemon development watcher and esbuilder with:

    npm run dev

# Building a web application with this library:  

See src/server.js for an example of how to initiailize a simple application with routes and responses.


# Features / Notes about this library:

* You can implement basic middleware, see src/lib/middleware.js for the api, basically just pass an object that implements handleResponse(req, res), and then pass that to yourApp.use(yourMiddleware).
* It's built with efficiency in mind, using only what's necessary (Application -> Router -> Response), all with only necessary implementation helpers. Classes are not used unless (only for application startup and non-performant sections) to keep code minimal.
* The built-in router uses a trie, the fastest implementation.
* All the configuration and data access is indexed and loaded at app startup, for fastest lookup and response from those method calls.

# API:

    Application {
        use(Middleware);    // register middleware to handle requests
        start();            // creates server and listens for requests
        stop();
    }
    
    Middleware {
        handleRequest(Request, Response, next);
    }

    Request {
        method: string;
        url:    string
    }

    Response {
        html(html, status = 200);
        text(text, status = 200);
        json(object, status = 200);
        error(error, status = 500);
        favicon(favicon);
        end(status = 200);
    }

    Router {
        get(url, handler);  // handler = (req, res) => {}
        put(url, handler);
        post(url, handler);
        patch(url, handler);
        delete(url, handler);
    }


# TODO:
* Have Application::onConnect not populate the socket methods for every request (move to helper class or prototype)
* Populate Request object with body and headers
* Add simple application config file support
* Implement Cookie handling...
* Add extended modules (CORS?)...