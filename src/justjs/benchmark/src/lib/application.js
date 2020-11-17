const tcp = require('./just-http-lib/tcp.js')
const http = require('./just-http-lib/http.js')
const { SystemError, print } = just
const { createServer } = tcp
const { createParser, HTTP_REQUEST, createHTTPServer } = http
const { createResponse } = require('./response.js');
const { log } = require('./utils/log');

// Todo: move this to config file / client layer

export default class JustWebApplication {
    config;

    // instantiated HTTP server instance
    server;

    // middleware stack
    middleware = [];

    // create and setup server instance
    constructor(config) {
        this.config = config;
        this.initServer();
    }

    initServer() {
        const self = this;
        this.server = createHTTPServer(createServer(this.config.ADDRESS, this.config.PORT), this.config.SERVER_NAME);
        this.server.reusePort(this.config.REUSE_PORT);
        this.server.reuseAddress(this.config.REUSE_ADDRESS);

        this.server.onConnect = sock => {

            /* 
             * TODO: All this should be moved into a static prototypical object so as to not assign so 
             * many properties during onConnect for each request, or otherwise moved into static 
             * helper class separate from socket instance itself.
             */

            // we should move this into lib/http.js but need to come up with a nicer
            // abstraction. this is just to show various bits of lower level plumbing
            const END = '\r\n\r\n';
            const buf = new ArrayBuffer(this.config.MAXHEADERS);
            const parser = createParser(buf, HTTP_REQUEST);

            parser.onRequests = count => {
                if (count === 1) {
                    // we have a single request (i.e. non-pipelined)
                    self.onRequest(parser.get(1)[0], sock);
                    return;
                }
                // if count > 1, we have multiple requests in the buffer we parsed
                for (const request of parser.get(count)) {
                    self.onRequest(request, sock);
                }
            }

            sock.setNoDelay(this.config.NO_DELAY); // TCP Nodelay / Disable Nagle
            sock.setKeepalive(this.config.KEEP_ALIVE); // TCP keepalive

            sock.onClose = () => {
                if (sock.timer) just.clearTimeout(sock.timer)
                parser.free()
            }

            sock.onData = bytes => parser.parse(bytes);
            sock.json = json => sock.writeString(`${this.server.rJSON}${json.length}${END}${json}`);
            sock.html = html => sock.writeString(`${this.server.rHTML}${html.length}${END}${html}`);
            sock.text = text => sock.writeString(`${this.server.rTEXT}${text.length}${END}${text}`);
            sock.error = err => sock.writeString(`${this.server.r500}${err.stack.length}${END}${err.stack}`);
            sock.favicon = favicon => {
                log("sending favicon...");
                const bytes = sock.writeString(`${this.server.favicon}${favicon.byteLength}${END}`);
                if (bytes < 0) return bytes;
                return sock.write(favicon);
            }

            return buf;
        }
    }

    // register a middleware
    use = (middleware) => {
        this.middleware.push(middleware);
        return this;
    }

    // start the server and listen
    start = () => {

        log(`Starting server: ${this.config.ADDRESS}:${this.config.PORT} ...`);

        let err = this.server.bind();
        if (err) 
            throw new SystemError('server.bind');
        
        err = this.server.listen();
        if (err)
            throw new SystemError('server.listen');

        if (this.config.MONITOR) {
            just.setInterval(() => {
                just.print(just.memoryUsage().rss);
            }, 1000);
        }

        return this;
    }

    // stop the server
    stop = () => {
        // todo: implement killing existing connections
    }

    onRequest = (req, socket) => {
        const res = createResponse(socket);
        let handled = this._passRequest(0, req, res);
        if (!handled) {
            log("Request not handled: " + url);
            res.end(404);
        }

        // For reference:

        // if (req.method === 'GET') {

        //     if (req.url === '/json') {
        //         if (sock.json(JSON.stringify(req)) < 0) just.error((new SystemError('sock.json')).stack)
        //         return
        //     }

        //     if (req.url === '/async') {
        //         // this will work fine due to head of line blocking in HTTP/1.1.
        //         // we won't receive another request on this socket until we send a complete response.
        //         // doing async if we support pipelined requests means we will need to maintain ordering
        //         // of responses on the socket
        //         sock.timer = just.setTimeout(() => {
        //             if (sock.json(JSON.stringify(req)) < 0) just.error((new SystemError('sock.json')).stack)
        //         }, 1000)
        //         return
        //     }

        //     if (req.url === '/favicon.ico') {
        //         if (sock.favicon(favicon) < 0) just.error((new SystemError('sock.favicon')).stack)
        //     }

        // }

        // if (sock.writeString(server.r404) < 0) just.error((new SystemError('sock.404')).stack)
    }



    // Todo: move all this to underlying class...

    // Passes request through middleware stack:
    // -Execute any code.
    // -Make changes to the request and the response objects.
    // -End the request-response cycle.
    // -Call the next middleware in the stack.
    _passRequest = (mwIndex, req, res) => {
        const self = this;
        if (this.middleware[mwIndex]) {
            this.middleware[mwIndex].handleRequest(req, res, function next() {
                self._passRequest(mwIndex+1, req, res);
            });
            return true;
        }
        return false;
    }

}