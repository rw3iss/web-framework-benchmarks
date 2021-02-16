var __create = Object.create;
var __defProp = Object.defineProperty;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __markAsModule = (target) => __defProp(target, "__esModule", {value: true});
var __commonJS = (callback, module2) => () => {
  if (!module2) {
    module2 = {exports: {}};
    callback(module2.exports, module2);
  }
  return module2.exports;
};
var __export = (target, all) => {
  __markAsModule(target);
  for (var name in all)
    __defProp(target, name, {get: all[name], enumerable: true});
};
var __exportStar = (target, module2, desc) => {
  __markAsModule(target);
  if (typeof module2 === "object" || typeof module2 === "function") {
    for (let key of __getOwnPropNames(module2))
      if (!__hasOwnProp.call(target, key) && key !== "default")
        __defProp(target, key, {get: () => module2[key], enumerable: !(desc = __getOwnPropDesc(module2, key)) || desc.enumerable});
  }
  return target;
};
var __toModule = (module2) => {
  if (module2 && module2.__esModule)
    return module2;
  return __exportStar(__defProp(__create(__getProtoOf(module2)), "default", {value: module2, enumerable: true}), module2);
};

// src/lib/just-http-lib/tcp.js
var require_tcp = __commonJS((exports, module2) => {
  const {sys, net} = just;
  const {EPOLLIN, EPOLLERR, EPOLLHUP, EPOLLOUT} = just.loop;
  const {IPPROTO_TCP, O_NONBLOCK, TCP_NODELAY, SO_KEEPALIVE, SOMAXCONN, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR, SO_REUSEPORT, SOCK_NONBLOCK, SO_ERROR} = net;
  const {loop} = just.factory;
  const readableMask = EPOLLIN | EPOLLERR | EPOLLHUP;
  const readableWritableMask = EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLOUT;
  function createServer2(host = "127.0.0.1", port = 3e3) {
    const server = {host, port};
    const sockets = {};
    function closeSocket(sock) {
      const {fd} = sock;
      sock.onClose && sock.onClose(sock);
      delete sockets[fd];
      loop.remove(fd);
      net.close(fd);
    }
    function onConnect(fd, event) {
      if (event & EPOLLERR || event & EPOLLHUP) {
        return closeSocket({fd});
      }
      const clientfd = net.accept(fd);
      const socket = sockets[clientfd] = {fd: clientfd};
      net.setsockopt(clientfd, IPPROTO_TCP, TCP_NODELAY, 0);
      net.setsockopt(clientfd, SOL_SOCKET, SO_KEEPALIVE, 0);
      loop.add(clientfd, (fd2, event2) => {
        if (event2 & EPOLLERR || event2 & EPOLLHUP) {
          return closeSocket(socket);
        }
        const {offset} = buffer;
        const bytes = net.recv(fd2, buffer, offset, byteLength - offset);
        if (bytes > 0) {
          socket.onData(bytes);
          return;
        }
        if (bytes < 0) {
          const errno = sys.errno();
          if (errno === net.EAGAIN)
            return;
          just.error(`recv error: ${sys.strerror(errno)} (${errno})`);
        }
        closeSocket(socket);
      });
      let flags = sys.fcntl(clientfd, sys.F_GETFL, 0);
      flags |= O_NONBLOCK;
      sys.fcntl(clientfd, sys.F_SETFL, flags);
      loop.update(clientfd, readableMask);
      socket.write = (buf, len = byteLength, off = 0) => {
        const written = net.send(clientfd, buf, len, off);
        if (written > 0) {
          return written;
        }
        if (written < 0) {
          const errno = sys.errno();
          if (errno === net.EAGAIN)
            return written;
          just.error(`write error (${clientfd}): ${sys.strerror(errno)} (${errno})`);
        }
        if (written === 0) {
          just.error(`zero write ${clientfd}`);
        }
        return written;
      };
      socket.writeString = (str) => net.sendString(clientfd, str);
      socket.close = () => closeSocket(socket);
      socket.setNoDelay = (on) => net.setsockopt(clientfd, IPPROTO_TCP, TCP_NODELAY, on ? 1 : 0);
      socket.setKeepalive = (on) => net.setsockopt(clientfd, SOL_SOCKET, SO_KEEPALIVE, on ? 1 : 0);
      const buffer = server.onConnect(socket);
      const byteLength = buffer.byteLength;
      buffer.offset = 0;
    }
    function listen(maxconn = SOMAXCONN) {
      const r = net.listen(sockfd, maxconn);
      if (r === 0)
        loop.add(sockfd, onConnect);
      return r;
    }
    const sockfd = net.socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    net.setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 1);
    net.setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, 1);
    server.reuseAddress = (on) => net.setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, on ? 1 : 0);
    server.reusePort = (on) => net.setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, on ? 1 : 0);
    server.bind = () => net.bind(sockfd, host, port);
    server.listen = listen;
    return server;
  }
  function createClient(address = "127.0.0.1", port = 3e3) {
    const sock = {address, port, connected: false};
    let fd;
    let byteLength = 0;
    function closeSocket() {
      sock.onClose && sock.onClose(sock);
      loop.remove(fd);
      net.close(fd);
    }
    function handleRead(fd2, event) {
      const {offset} = buffer;
      const bytes = net.recv(fd2, buffer, offset, byteLength - offset);
      if (bytes > 0) {
        sock.onData(bytes);
        return;
      }
      if (bytes < 0) {
        const errno = sys.errno();
        if (errno === net.EAGAIN)
          return;
        just.print(`recv error: ${sys.strerror(errno)} (${errno})`);
      }
      closeSocket(sock);
    }
    function handleError(fd2, event) {
      const errno = net.getsockopt(fd2, SOL_SOCKET, SO_ERROR);
      if (!sock.connected) {
        sock.onConnect(new Error(`${errno} : ${just.sys.strerror(errno)}`));
      }
    }
    function handleWrite(fd2, event) {
      if (!sock.connected) {
        net.setsockopt(fd2, IPPROTO_TCP, TCP_NODELAY, 0);
        net.setsockopt(fd2, SOL_SOCKET, SO_KEEPALIVE, 0);
        let flags = sys.fcntl(fd2, sys.F_GETFL, 0);
        flags |= O_NONBLOCK;
        sys.fcntl(fd2, sys.F_SETFL, flags);
        loop.update(fd2, readableMask);
        sock.setNoDelay = (on) => net.setsockopt(fd2, IPPROTO_TCP, TCP_NODELAY, on ? 1 : 0);
        sock.setKeepalive = (on) => net.setsockopt(fd2, SOL_SOCKET, SO_KEEPALIVE, on ? 1 : 0);
        buffer = sock.onConnect(null, sock);
        byteLength = buffer.byteLength;
        buffer.offset = 0;
        sock.connected = true;
      }
    }
    function onSocketEvent(fd2, event) {
      if (event & EPOLLERR || event & EPOLLHUP) {
        handleError(fd2, event);
        closeSocket();
        return;
      }
      if (event & EPOLLIN) {
        handleRead(fd2, event);
      }
      if (event & EPOLLOUT) {
        handleWrite(fd2, event);
      }
    }
    sock.write = (buf, len = buf.byteLength, off = 0) => {
      const written = net.send(fd, buf, len, off);
      if (written > 0) {
        return written;
      }
      if (written < 0) {
        const errno = sys.errno();
        if (errno === net.EAGAIN)
          return written;
        just.error(`write error (${fd}): ${sys.strerror(errno)} (${errno})`);
      }
      if (written === 0) {
        just.error(`zero write ${fd}`);
      }
      return written;
    };
    sock.writeString = (str) => net.sendString(fd, str);
    sock.close = () => closeSocket(sock);
    function connect() {
      fd = net.socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
      loop.add(fd, onSocketEvent, readableWritableMask);
      net.connect(fd, address, port);
      sock.fd = fd;
      return sock;
    }
    let buffer;
    sock.connect = connect;
    return sock;
  }
  module2.exports = {createServer: createServer2, createClient};
});

// src/lib/just-http-lib/http.js
var require_http = __commonJS((exports, module2) => {
  const {http: http2} = just.library("http.so", "http");
  const {
    parseResponses,
    getResponses,
    parseRequests,
    getStatusCode,
    getStatusMessage,
    getHeaders,
    getRequests,
    getMethod,
    getUrl
  } = http2;
  const free = {request: [], response: []};
  function chunkedParser(buf) {
    let inHeader = true;
    let offset = 0;
    let chunkLen = 0;
    let ending = false;
    const digits = [];
    const u8 = new Uint8Array(buf);
    function parse(bytes) {
      offset = buf.offset;
      while (bytes) {
        if (inHeader) {
          const c = u8[offset];
          offset++;
          bytes--;
          if (c === 13) {
            continue;
          } else if (c === 10) {
            if (ending) {
              buf.offset = offset;
              parser.onEnd();
              ending = false;
              continue;
            }
            if (digits.length) {
              chunkLen = parseInt(`0x${digits.join("")}`);
              if (chunkLen > 0) {
                inHeader = false;
              } else if (chunkLen === 0) {
                ending = true;
              }
              digits.length = 0;
            }
            continue;
          } else if (c > 47 && c < 58) {
            digits.push(String.fromCharCode(c));
            continue;
          } else if (c > 96 && c < 103) {
            digits.push(String.fromCharCode(c));
            continue;
          } else if (c > 64 && c < 71) {
            digits.push(String.fromCharCode(c));
            continue;
          } else {
            just.print("BAD_CHAR");
          }
          just.print("OOB:");
          just.print(`c ${c}`);
          just.print(`bytes ${bytes}`);
          just.print(`offset ${offset}`);
          just.print(`chunkLen ${chunkLen}`);
          throw new Error("OOB");
        } else {
          if (bytes >= chunkLen) {
            buf.offset = offset;
            parser.onData(chunkLen);
            inHeader = true;
            offset += chunkLen;
            bytes -= chunkLen;
            chunkLen = 0;
          } else {
            buf.offset = offset;
            parser.onData(bytes);
            chunkLen -= bytes;
            bytes = 0;
          }
        }
        buf.offset = offset;
      }
    }
    function reset() {
    }
    const parser = {parse, reset};
    return parser;
  }
  function requestParser(buffer) {
    if (free.length) {
      const parser2 = free.request.shift();
      parser2.buffer.offset = 0;
      return parser2;
    }
    const answer = [0];
    const parser = {buffer};
    function parse(bytes, off = 0) {
      const {offset} = buffer;
      const count = parseRequests(buffer, offset + bytes, off, answer);
      if (count > 0) {
        parser.onRequests(count);
      }
      const [remaining] = answer;
      if (remaining > 0) {
        const start = offset + bytes - remaining;
        const len = remaining;
        if (start > offset) {
          buffer.copyFrom(buffer, 0, len, start);
        }
        buffer.offset = len;
        return;
      }
      buffer.offset = 0;
    }
    buffer.offset = 0;
    parser.parse = parse;
    parser.get = (count) => getRequests(count);
    parser.url = (index) => getUrl(index);
    parser.method = (index) => getMethod(index);
    parser.headers = (index) => getHeaders(index);
    parser.free = () => free.request.push(parser);
    return parser;
  }
  function responseParser(buffer) {
    if (free.length) {
      const parser2 = free.response.shift();
      parser2.buffer.offset = 0;
      return parser2;
    }
    const answer = [0];
    const parser = {buffer};
    function parse(bytes, off = 0) {
      const {offset} = buffer;
      const count = parseResponses(buffer, offset + bytes, offset, answer);
      const [remaining] = answer;
      if (remaining > 0) {
        const start = offset + bytes - remaining;
        buffer.offset = start;
        buffer.remaining = remaining;
        if (count > 0) {
          parser.onResponses(count);
        }
      } else {
        if (count > 0) {
          parser.onResponses(count);
        }
      }
      buffer.offset = 0;
    }
    buffer.offset = 0;
    parser.parse = parse;
    parser.get = (count) => getResponses(count);
    parser.status = (index) => ({code: getStatusCode(index), message: getStatusMessage(index)});
    parser.headers = (index) => getHeaders(index);
    parser.free = () => free.response.push(parser);
    return parser;
  }
  function createHTTPServer2(server, name = "j") {
    if (server.timer)
      just.clearInterval(server.timer);
    let time = new Date().toUTCString();
    server.rHTML = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: text/html; charset=UTF-8\r
Content-Length: `;
    server.rTEXT = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: text/plain\r
Content-Length: `;
    server.rJSON = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: application/json\r
Content-Length: `;
    server.r404 = `HTTP/1.1 404 Not Found\r
Server: ${name}\r
Date: ${time}\r
Content-Type: text/plain\r
Content-Length: 0\r
\r
`;
    server.favicon = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: image/vnd.microsoft.icon\r
Content-Length: `;
    server.timer = just.setInterval(() => {
      time = new Date().toUTCString();
      server.rHTML = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: text/html; charset=UTF-8\r
Content-Length: `;
      server.rTEXT = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: text/plain\r
Content-Length: `;
      server.rJSON = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: application/json\r
Content-Length: `;
      server.r404 = `HTTP/1.1 404 Not Found\r
Server: ${name}\r
Date: ${time}\r
Content-Type: text/plain\r
Content-Length: 0\r
\r
`;
      server.favicon = `HTTP/1.1 200 OK\r
Server: ${name}\r
Date: ${time}\r
Content-Type: image/vnd.microsoft.icon\r
Content-Length: `;
    }, 500);
    return server;
  }
  const [HTTP_REQUEST2, HTTP_RESPONSE, HTTP_CHUNKED] = [0, 1, 2];
  const create = {[HTTP_CHUNKED]: chunkedParser, [HTTP_REQUEST2]: requestParser, [HTTP_RESPONSE]: responseParser};
  function createParser2(buffer, type = HTTP_REQUEST2) {
    return create[type](buffer);
  }
  module2.exports = {createParser: createParser2, createHTTPServer: createHTTPServer2, HTTP_RESPONSE, HTTP_REQUEST: HTTP_REQUEST2, HTTP_CHUNKED};
});

// src/lib/response.js
var require_response = __commonJS((exports, module2) => {
  function Response(socket) {
    this.socket = socket;
    return this;
  }
  Response.prototype.html = function(html, status = 200) {
    if (this.socket.html(html) < 0)
      just.error(new SystemError("sock.html").stack);
    this.socket.close();
  };
  Response.prototype.text = function(text, status = 200) {
    if (this.socket.text(text) < 0)
      just.error(new SystemError("sock.text").stack);
    this.socket.close();
  };
  Response.prototype.json = function(object, status = 200) {
    let jm = JSON.stringify(object);
    if (this.socket.json(jm) < 0)
      just.error(new SystemError("sock.json").stack);
    this.socket.close();
  };
  Response.prototype.favicon = function(favicon2) {
    if (this.socket.favicon(favicon2) < 0)
      just.error(new SystemError("sock.favicon").stack);
    this.socket.close();
  };
  Response.prototype.error = function(error, status = 500) {
    if (this.socket.error(error) < 0)
      just.error(new SystemError("sock.error").stack);
    this.socket.close();
  };
  Response.prototype.end = function(status = 200) {
    this.text("", status);
  };
  function createResponse2(socket) {
    return new Response(socket);
  }
  module2.exports = {createResponse: createResponse2};
});

// src/lib/utils/log.js
var require_log = __commonJS((exports) => {
  __export(exports, {
    log: () => log3
  });
  const {print: print3} = just;
  function log3(...args) {
    args.forEach((v) => {
      if (typeof v == "object") {
        print3(JSON.stringify(v));
      } else {
        print3(v);
      }
    });
  }
});

// src/lib/router/lib/router.js
var require_router = __commonJS((exports, module2) => {
  function Router2(options) {
    if (!(this instanceof Router2))
      return new Router2(options);
    this._init(options);
  }
  Router2.prototype._init = function(options) {
    options = options || {};
    this.child = Object.create(null);
    this.children = [];
    this.name = options.name || "";
    if (typeof options.string === "string")
      this.string = options.string;
    else if (typeof options.regex === "string")
      this.regex = new RegExp("^(" + options.regex + ")$", options.flag == null ? "i" : options.flag);
    else if (options.regex instanceof RegExp)
      this.regex = options.regex;
  };
  Router2.prototype._add = function(options) {
    return this._find(options) || this._attach(options);
  };
  Router2.prototype._find = function(options) {
    if (typeof options.string === "string")
      return this.child[options.string];
    var child;
    var children = this.children;
    var l = children.length;
    if (options.name) {
      for (var j = 0; j < l; j++)
        if ((child = children[j]).name === options.name)
          return child;
    }
  };
  Router2.prototype._attach = function(node) {
    if (!(node instanceof Router2))
      node = new Router2(node);
    node.parent = this;
    if (node.string == null)
      this.children.push(node);
    else
      this.child[node.string] = node;
    return node;
  };
  module2.exports = Router2;
});

// node_modules/flatten/index.js
var require_flatten = __commonJS((exports, module2) => {
  module2.exports = function flatten(list, depth) {
    depth = typeof depth == "number" ? depth : Infinity;
    if (!depth) {
      if (Array.isArray(list)) {
        return list.map(function(i) {
          return i;
        });
      }
      return list;
    }
    return _flatten(list, 1);
    function _flatten(list2, d) {
      return list2.reduce(function(acc, item) {
        if (Array.isArray(item) && d < depth) {
          return acc.concat(_flatten(item, d + 1));
        } else {
          return acc.concat(item);
        }
      }, []);
    }
  };
});

// src/lib/router/lib/define.js
var require_define = __commonJS(() => {
  var flatten = require_flatten();
  var Router2 = require_router();
  Router2.prototype.define = function(route) {
    if (typeof route !== "string")
      throw new TypeError("Only strings can be defined.");
    try {
      return Define(route.split("/"), this);
    } catch (err) {
      err.route = route;
      throw err;
    }
  };
  function Define(frags, root) {
    var frag = frags[0];
    var info = Router2.parse(frag);
    var name = info.name;
    var nodes = Object.keys(info.string).map(function(x) {
      return {
        name,
        string: x
      };
    });
    if (info.regex) {
      nodes.push({
        name,
        regex: info.regex
      });
    }
    if (!nodes.length) {
      nodes = [{
        name
      }];
    }
    nodes = nodes.map(root._add, root);
    return frags.length - 1 ? flatten(nodes.map(Define.bind(null, frags.slice(1)))) : nodes;
  }
});

// src/lib/router/lib/match.js
var require_match = __commonJS(() => {
  var Router2 = require_router();
  Router2.prototype.match = function(url4) {
    var root = this;
    var frags = url4.split("/");
    var length = frags.length;
    var match = {
      param: {}
    };
    var frag, node, nodes, regex, name;
    top:
      while (length) {
        frag = decode(frags.shift());
        if (frag === -1) {
          throw "Malformed URL: " + url4;
        }
        length = frags.length;
        if (node = root.child[frag]) {
          if (name = node.name)
            match.param[name] = frag;
          if (!length) {
            match.node = node;
            return match;
          }
          root = node;
          continue top;
        }
        nodes = root.children;
        for (var i = 0, l = nodes.length; i < l; i++) {
          node = nodes[i];
          if (!(regex = node.regex) || regex.test(frag)) {
            if (name = node.name)
              match.param[name] = frag;
            if (!length) {
              match.node = node;
              return match;
            }
            root = node;
            continue top;
          }
        }
        return;
      }
  };
  function decode(string) {
    try {
      return decodeURIComponent(string);
    } catch (err) {
      return -1;
    }
  }
});

// src/lib/router/lib/parse.js
var require_parse = __commonJS(() => {
  var Router2 = require_router();
  Router2.parse = function(string) {
    var options = Parse(string);
    if (!options) {
      throw "Invalid parsed string: " + string;
    }
    return options;
  };
  function Parse(string) {
    var options = {
      name: "",
      string: {},
      regex: ""
    };
    if (isValidSlug(string)) {
      options.string[string] = true;
      return options;
    }
    if (isPipeSeparatedString(string)) {
      string.split("|").forEach(function(x) {
        options.string[x] = true;
      });
      return options;
    }
    string = string.replace(/^\:\w+\b/, function(_) {
      options.name = _.slice(1);
      return "";
    });
    if (!string)
      return options;
    if (/^\(.+\)$/.test(string) && (string = string.slice(1, -1))) {
      if (isPipeSeparatedString(string))
        string.split("|").filter(function(x) {
          options.string[x] = true;
        });
      else
        options.regex = string;
      return options;
    }
  }
  function isValidSlug(x) {
    return x === "" || /^[\w\.-]+$/.test(x);
  }
  function isPipeSeparatedString(x) {
    return /^[\w\.\-][\w\.\-\|]+[\w\.\-]$/.test(x);
  }
});

// node_modules/url/util.js
var require_util = __commonJS((exports, module2) => {
  "use strict";
  module2.exports = {
    isString: function(arg) {
      return typeof arg === "string";
    },
    isObject: function(arg) {
      return typeof arg === "object" && arg !== null;
    },
    isNull: function(arg) {
      return arg === null;
    },
    isNullOrUndefined: function(arg) {
      return arg == null;
    }
  };
});

// node_modules/url/url.js
var require_url = __commonJS((exports) => {
  "use strict";
  var punycode = require("punycode");
  var util = require_util();
  exports.parse = urlParse;
  exports.resolve = urlResolve;
  exports.resolveObject = urlResolveObject;
  exports.format = urlFormat;
  exports.Url = Url;
  function Url() {
    this.protocol = null;
    this.slashes = null;
    this.auth = null;
    this.host = null;
    this.port = null;
    this.hostname = null;
    this.hash = null;
    this.search = null;
    this.query = null;
    this.pathname = null;
    this.path = null;
    this.href = null;
  }
  var protocolPattern = /^([a-z0-9.+-]+:)/i;
  var portPattern = /:[0-9]*$/;
  var simplePathPattern = /^(\/\/?(?!\/)[^\?\s]*)(\?[^\s]*)?$/;
  var delims = ["<", ">", '"', "`", " ", "\r", "\n", "	"];
  var unwise = ["{", "}", "|", "\\", "^", "`"].concat(delims);
  var autoEscape = ["'"].concat(unwise);
  var nonHostChars = ["%", "/", "?", ";", "#"].concat(autoEscape);
  var hostEndingChars = ["/", "?", "#"];
  var hostnameMaxLen = 255;
  var hostnamePartPattern = /^[+a-z0-9A-Z_-]{0,63}$/;
  var hostnamePartStart = /^([+a-z0-9A-Z_-]{0,63})(.*)$/;
  var unsafeProtocol = {
    javascript: true,
    "javascript:": true
  };
  var hostlessProtocol = {
    javascript: true,
    "javascript:": true
  };
  var slashedProtocol = {
    http: true,
    https: true,
    ftp: true,
    gopher: true,
    file: true,
    "http:": true,
    "https:": true,
    "ftp:": true,
    "gopher:": true,
    "file:": true
  };
  var querystring = require("querystring");
  function urlParse(url4, parseQueryString, slashesDenoteHost) {
    if (url4 && util.isObject(url4) && url4 instanceof Url)
      return url4;
    var u = new Url();
    u.parse(url4, parseQueryString, slashesDenoteHost);
    return u;
  }
  Url.prototype.parse = function(url4, parseQueryString, slashesDenoteHost) {
    if (!util.isString(url4)) {
      throw new TypeError("Parameter 'url' must be a string, not " + typeof url4);
    }
    var queryIndex = url4.indexOf("?"), splitter = queryIndex !== -1 && queryIndex < url4.indexOf("#") ? "?" : "#", uSplit = url4.split(splitter), slashRegex = /\\/g;
    uSplit[0] = uSplit[0].replace(slashRegex, "/");
    url4 = uSplit.join(splitter);
    var rest = url4;
    rest = rest.trim();
    if (!slashesDenoteHost && url4.split("#").length === 1) {
      var simplePath = simplePathPattern.exec(rest);
      if (simplePath) {
        this.path = rest;
        this.href = rest;
        this.pathname = simplePath[1];
        if (simplePath[2]) {
          this.search = simplePath[2];
          if (parseQueryString) {
            this.query = querystring.parse(this.search.substr(1));
          } else {
            this.query = this.search.substr(1);
          }
        } else if (parseQueryString) {
          this.search = "";
          this.query = {};
        }
        return this;
      }
    }
    var proto = protocolPattern.exec(rest);
    if (proto) {
      proto = proto[0];
      var lowerProto = proto.toLowerCase();
      this.protocol = lowerProto;
      rest = rest.substr(proto.length);
    }
    if (slashesDenoteHost || proto || rest.match(/^\/\/[^@\/]+@[^@\/]+/)) {
      var slashes = rest.substr(0, 2) === "//";
      if (slashes && !(proto && hostlessProtocol[proto])) {
        rest = rest.substr(2);
        this.slashes = true;
      }
    }
    if (!hostlessProtocol[proto] && (slashes || proto && !slashedProtocol[proto])) {
      var hostEnd = -1;
      for (var i = 0; i < hostEndingChars.length; i++) {
        var hec = rest.indexOf(hostEndingChars[i]);
        if (hec !== -1 && (hostEnd === -1 || hec < hostEnd))
          hostEnd = hec;
      }
      var auth, atSign;
      if (hostEnd === -1) {
        atSign = rest.lastIndexOf("@");
      } else {
        atSign = rest.lastIndexOf("@", hostEnd);
      }
      if (atSign !== -1) {
        auth = rest.slice(0, atSign);
        rest = rest.slice(atSign + 1);
        this.auth = decodeURIComponent(auth);
      }
      hostEnd = -1;
      for (var i = 0; i < nonHostChars.length; i++) {
        var hec = rest.indexOf(nonHostChars[i]);
        if (hec !== -1 && (hostEnd === -1 || hec < hostEnd))
          hostEnd = hec;
      }
      if (hostEnd === -1)
        hostEnd = rest.length;
      this.host = rest.slice(0, hostEnd);
      rest = rest.slice(hostEnd);
      this.parseHost();
      this.hostname = this.hostname || "";
      var ipv6Hostname = this.hostname[0] === "[" && this.hostname[this.hostname.length - 1] === "]";
      if (!ipv6Hostname) {
        var hostparts = this.hostname.split(/\./);
        for (var i = 0, l = hostparts.length; i < l; i++) {
          var part = hostparts[i];
          if (!part)
            continue;
          if (!part.match(hostnamePartPattern)) {
            var newpart = "";
            for (var j = 0, k = part.length; j < k; j++) {
              if (part.charCodeAt(j) > 127) {
                newpart += "x";
              } else {
                newpart += part[j];
              }
            }
            if (!newpart.match(hostnamePartPattern)) {
              var validParts = hostparts.slice(0, i);
              var notHost = hostparts.slice(i + 1);
              var bit = part.match(hostnamePartStart);
              if (bit) {
                validParts.push(bit[1]);
                notHost.unshift(bit[2]);
              }
              if (notHost.length) {
                rest = "/" + notHost.join(".") + rest;
              }
              this.hostname = validParts.join(".");
              break;
            }
          }
        }
      }
      if (this.hostname.length > hostnameMaxLen) {
        this.hostname = "";
      } else {
        this.hostname = this.hostname.toLowerCase();
      }
      if (!ipv6Hostname) {
        this.hostname = punycode.toASCII(this.hostname);
      }
      var p = this.port ? ":" + this.port : "";
      var h = this.hostname || "";
      this.host = h + p;
      this.href += this.host;
      if (ipv6Hostname) {
        this.hostname = this.hostname.substr(1, this.hostname.length - 2);
        if (rest[0] !== "/") {
          rest = "/" + rest;
        }
      }
    }
    if (!unsafeProtocol[lowerProto]) {
      for (var i = 0, l = autoEscape.length; i < l; i++) {
        var ae = autoEscape[i];
        if (rest.indexOf(ae) === -1)
          continue;
        var esc = encodeURIComponent(ae);
        if (esc === ae) {
          esc = escape(ae);
        }
        rest = rest.split(ae).join(esc);
      }
    }
    var hash = rest.indexOf("#");
    if (hash !== -1) {
      this.hash = rest.substr(hash);
      rest = rest.slice(0, hash);
    }
    var qm = rest.indexOf("?");
    if (qm !== -1) {
      this.search = rest.substr(qm);
      this.query = rest.substr(qm + 1);
      if (parseQueryString) {
        this.query = querystring.parse(this.query);
      }
      rest = rest.slice(0, qm);
    } else if (parseQueryString) {
      this.search = "";
      this.query = {};
    }
    if (rest)
      this.pathname = rest;
    if (slashedProtocol[lowerProto] && this.hostname && !this.pathname) {
      this.pathname = "/";
    }
    if (this.pathname || this.search) {
      var p = this.pathname || "";
      var s = this.search || "";
      this.path = p + s;
    }
    this.href = this.format();
    return this;
  };
  function urlFormat(obj) {
    if (util.isString(obj))
      obj = urlParse(obj);
    if (!(obj instanceof Url))
      return Url.prototype.format.call(obj);
    return obj.format();
  }
  Url.prototype.format = function() {
    var auth = this.auth || "";
    if (auth) {
      auth = encodeURIComponent(auth);
      auth = auth.replace(/%3A/i, ":");
      auth += "@";
    }
    var protocol = this.protocol || "", pathname = this.pathname || "", hash = this.hash || "", host = false, query = "";
    if (this.host) {
      host = auth + this.host;
    } else if (this.hostname) {
      host = auth + (this.hostname.indexOf(":") === -1 ? this.hostname : "[" + this.hostname + "]");
      if (this.port) {
        host += ":" + this.port;
      }
    }
    if (this.query && util.isObject(this.query) && Object.keys(this.query).length) {
      query = querystring.stringify(this.query);
    }
    var search = this.search || query && "?" + query || "";
    if (protocol && protocol.substr(-1) !== ":")
      protocol += ":";
    if (this.slashes || (!protocol || slashedProtocol[protocol]) && host !== false) {
      host = "//" + (host || "");
      if (pathname && pathname.charAt(0) !== "/")
        pathname = "/" + pathname;
    } else if (!host) {
      host = "";
    }
    if (hash && hash.charAt(0) !== "#")
      hash = "#" + hash;
    if (search && search.charAt(0) !== "?")
      search = "?" + search;
    pathname = pathname.replace(/[?#]/g, function(match) {
      return encodeURIComponent(match);
    });
    search = search.replace("#", "%23");
    return protocol + host + pathname + search + hash;
  };
  function urlResolve(source, relative) {
    return urlParse(source, false, true).resolve(relative);
  }
  Url.prototype.resolve = function(relative) {
    return this.resolveObject(urlParse(relative, false, true)).format();
  };
  function urlResolveObject(source, relative) {
    if (!source)
      return relative;
    return urlParse(source, false, true).resolveObject(relative);
  }
  Url.prototype.resolveObject = function(relative) {
    if (util.isString(relative)) {
      var rel = new Url();
      rel.parse(relative, false, true);
      relative = rel;
    }
    var result = new Url();
    var tkeys = Object.keys(this);
    for (var tk = 0; tk < tkeys.length; tk++) {
      var tkey = tkeys[tk];
      result[tkey] = this[tkey];
    }
    result.hash = relative.hash;
    if (relative.href === "") {
      result.href = result.format();
      return result;
    }
    if (relative.slashes && !relative.protocol) {
      var rkeys = Object.keys(relative);
      for (var rk = 0; rk < rkeys.length; rk++) {
        var rkey = rkeys[rk];
        if (rkey !== "protocol")
          result[rkey] = relative[rkey];
      }
      if (slashedProtocol[result.protocol] && result.hostname && !result.pathname) {
        result.path = result.pathname = "/";
      }
      result.href = result.format();
      return result;
    }
    if (relative.protocol && relative.protocol !== result.protocol) {
      if (!slashedProtocol[relative.protocol]) {
        var keys = Object.keys(relative);
        for (var v = 0; v < keys.length; v++) {
          var k = keys[v];
          result[k] = relative[k];
        }
        result.href = result.format();
        return result;
      }
      result.protocol = relative.protocol;
      if (!relative.host && !hostlessProtocol[relative.protocol]) {
        var relPath = (relative.pathname || "").split("/");
        while (relPath.length && !(relative.host = relPath.shift()))
          ;
        if (!relative.host)
          relative.host = "";
        if (!relative.hostname)
          relative.hostname = "";
        if (relPath[0] !== "")
          relPath.unshift("");
        if (relPath.length < 2)
          relPath.unshift("");
        result.pathname = relPath.join("/");
      } else {
        result.pathname = relative.pathname;
      }
      result.search = relative.search;
      result.query = relative.query;
      result.host = relative.host || "";
      result.auth = relative.auth;
      result.hostname = relative.hostname || relative.host;
      result.port = relative.port;
      if (result.pathname || result.search) {
        var p = result.pathname || "";
        var s = result.search || "";
        result.path = p + s;
      }
      result.slashes = result.slashes || relative.slashes;
      result.href = result.format();
      return result;
    }
    var isSourceAbs = result.pathname && result.pathname.charAt(0) === "/", isRelAbs = relative.host || relative.pathname && relative.pathname.charAt(0) === "/", mustEndAbs = isRelAbs || isSourceAbs || result.host && relative.pathname, removeAllDots = mustEndAbs, srcPath = result.pathname && result.pathname.split("/") || [], relPath = relative.pathname && relative.pathname.split("/") || [], psychotic = result.protocol && !slashedProtocol[result.protocol];
    if (psychotic) {
      result.hostname = "";
      result.port = null;
      if (result.host) {
        if (srcPath[0] === "")
          srcPath[0] = result.host;
        else
          srcPath.unshift(result.host);
      }
      result.host = "";
      if (relative.protocol) {
        relative.hostname = null;
        relative.port = null;
        if (relative.host) {
          if (relPath[0] === "")
            relPath[0] = relative.host;
          else
            relPath.unshift(relative.host);
        }
        relative.host = null;
      }
      mustEndAbs = mustEndAbs && (relPath[0] === "" || srcPath[0] === "");
    }
    if (isRelAbs) {
      result.host = relative.host || relative.host === "" ? relative.host : result.host;
      result.hostname = relative.hostname || relative.hostname === "" ? relative.hostname : result.hostname;
      result.search = relative.search;
      result.query = relative.query;
      srcPath = relPath;
    } else if (relPath.length) {
      if (!srcPath)
        srcPath = [];
      srcPath.pop();
      srcPath = srcPath.concat(relPath);
      result.search = relative.search;
      result.query = relative.query;
    } else if (!util.isNullOrUndefined(relative.search)) {
      if (psychotic) {
        result.hostname = result.host = srcPath.shift();
        var authInHost = result.host && result.host.indexOf("@") > 0 ? result.host.split("@") : false;
        if (authInHost) {
          result.auth = authInHost.shift();
          result.host = result.hostname = authInHost.shift();
        }
      }
      result.search = relative.search;
      result.query = relative.query;
      if (!util.isNull(result.pathname) || !util.isNull(result.search)) {
        result.path = (result.pathname ? result.pathname : "") + (result.search ? result.search : "");
      }
      result.href = result.format();
      return result;
    }
    if (!srcPath.length) {
      result.pathname = null;
      if (result.search) {
        result.path = "/" + result.search;
      } else {
        result.path = null;
      }
      result.href = result.format();
      return result;
    }
    var last = srcPath.slice(-1)[0];
    var hasTrailingSlash = (result.host || relative.host || srcPath.length > 1) && (last === "." || last === "..") || last === "";
    var up = 0;
    for (var i = srcPath.length; i >= 0; i--) {
      last = srcPath[i];
      if (last === ".") {
        srcPath.splice(i, 1);
      } else if (last === "..") {
        srcPath.splice(i, 1);
        up++;
      } else if (up) {
        srcPath.splice(i, 1);
        up--;
      }
    }
    if (!mustEndAbs && !removeAllDots) {
      for (; up--; up) {
        srcPath.unshift("..");
      }
    }
    if (mustEndAbs && srcPath[0] !== "" && (!srcPath[0] || srcPath[0].charAt(0) !== "/")) {
      srcPath.unshift("");
    }
    if (hasTrailingSlash && srcPath.join("/").substr(-1) !== "/") {
      srcPath.push("");
    }
    var isAbsolute = srcPath[0] === "" || srcPath[0] && srcPath[0].charAt(0) === "/";
    if (psychotic) {
      result.hostname = result.host = isAbsolute ? "" : srcPath.length ? srcPath.shift() : "";
      var authInHost = result.host && result.host.indexOf("@") > 0 ? result.host.split("@") : false;
      if (authInHost) {
        result.auth = authInHost.shift();
        result.host = result.hostname = authInHost.shift();
      }
    }
    mustEndAbs = mustEndAbs || result.host && srcPath.length;
    if (mustEndAbs && !isAbsolute) {
      srcPath.unshift("");
    }
    if (!srcPath.length) {
      result.pathname = null;
      result.path = null;
    } else {
      result.pathname = srcPath.join("/");
    }
    if (!util.isNull(result.pathname) || !util.isNull(result.search)) {
      result.path = (result.pathname ? result.pathname : "") + (result.search ? result.search : "");
    }
    result.auth = relative.auth || result.auth;
    result.slashes = result.slashes || relative.slashes;
    result.href = result.format();
    return result;
  };
  Url.prototype.parseHost = function() {
    var host = this.host;
    var port = portPattern.exec(host);
    if (port) {
      port = port[0];
      if (port !== ":") {
        this.port = port.substr(1);
      }
      host = host.substr(0, host.length - port.length);
    }
    if (host)
      this.hostname = host;
  };
});

// src/lib/application.js
const tcp = require_tcp();
const http = require_http();
const {SystemError: SystemError2, print} = just;
const {createServer} = tcp;
const {createParser, HTTP_REQUEST, createHTTPServer} = http;
const {createResponse} = require_response();
const {log} = require_log();
class JustWebApplication {
  config;
  server;
  middleware = [];
  constructor(config2) {
    this.config = config2;
    this.initServer();
  }
  initServer() {
    const self = this;
    this.server = createHTTPServer(createServer(this.config.ADDRESS, this.config.PORT), this.config.SERVER_NAME);
    this.server.reusePort(this.config.REUSE_PORT);
    this.server.reuseAddress(this.config.REUSE_ADDRESS);
    this.server.onConnect = (sock) => {
      const END = "\r\n\r\n";
      const buf = new ArrayBuffer(this.config.MAXHEADERS);
      const parser = createParser(buf, HTTP_REQUEST);
      parser.onRequests = (count) => {
        if (count === 1) {
          self.onRequest(parser.get(1)[0], sock);
          return;
        }
        for (const request of parser.get(count)) {
          self.onRequest(request, sock);
        }
      };
      sock.setNoDelay(this.config.NO_DELAY);
      sock.setKeepalive(this.config.KEEP_ALIVE);
      sock.onClose = () => {
        if (sock.timer)
          just.clearTimeout(sock.timer);
        parser.free();
      };
      sock.onData = (bytes) => parser.parse(bytes);
      sock.json = (json) => sock.writeString(`${this.server.rJSON}${json.length}${END}${json}`);
      sock.html = (html) => sock.writeString(`${this.server.rHTML}${html.length}${END}${html}`);
      sock.text = (text) => sock.writeString(`${this.server.rTEXT}${text.length}${END}${text}`);
      sock.error = (err) => sock.writeString(`${this.server.r500}${err.stack.length}${END}${err.stack}`);
      sock.favicon = (favicon2) => {
        log("sending favicon...");
        const bytes = sock.writeString(`${this.server.favicon}${favicon2.byteLength}${END}`);
        if (bytes < 0)
          return bytes;
        return sock.write(favicon2);
      };
      return buf;
    };
  }
  use = (middleware2) => {
    this.middleware.push(middleware2);
    return this;
  };
  start = () => {
    log(`Starting server:  ${this.config.ADDRESS}:${this.config.PORT} ...`);
    let err = this.server.bind();
    if (err)
      throw new SystemError2("server.bind");
    err = this.server.listen();
    if (err)
      throw new SystemError2("server.listen");
    if (this.config.MONITOR) {
      just.setInterval(() => {
        just.print(just.memoryUsage().rss);
      }, 1e3);
    }
    return this;
  };
  stop = () => {
  };
  onRequest = (req, socket) => {
    const res = createResponse(socket);
    let handled = this._passRequest(0, req, res);
    if (!handled) {
      log("Request not handled: " + url);
      res.end(404);
    }
  };
  _passRequest = (mwIndex, req, res) => {
    const self = this;
    if (this.middleware[mwIndex]) {
      this.middleware[mwIndex].handleRequest(req, res, function next() {
        self._passRequest(mwIndex + 1, req, res);
      });
      return true;
    }
    return false;
  };
}

// src/lib/router/lib/index.js
let _Router = require_router();
require_define();
require_match();
require_parse();
var lib_default = _Router;

// src/lib/middleware.js
class Middleware {
  handleRequest(req, res, next) {
    next();
  }
}

// src/lib/router/index.js
const url2 = __toModule(require_url());
const {print: print2} = just;
const router = new lib_default();
class Router extends Middleware {
  static get(path, handler) {
    var node = router.define(path)[0];
    node.GET = node.GET || [];
    node.GET.push(handler);
  }
  static post(path, handler) {
    var node = router.define(path)[0];
    node.POST = node.POST || [];
    node.POST.push(handler);
  }
  static put(path, handler) {
    var node = router.define(path)[0];
    node.PUT = node.PUT || [];
    node.PUT.push(handler);
  }
  static patch(path, handler) {
    var node = router.define(path)[0];
    node.PATCH = node.PATCH || [];
    node.PATCH.push(handler);
  }
  static delete(path, handler) {
    var node = router.define(path)[0];
    node.DELETE = node.DELETE || [];
    node.DELETE.push(handler);
  }
  static handleRequest(req, res, next) {
    var match = router.match(url2.default.parse(req.url).pathname);
    if (!match) {
      print2("404: " + req.url);
      return next();
    }
    var node = match.node;
    var callbacks = node[req.method];
    if (!callbacks) {
      print2("405...");
      return;
    }
    callbacks.forEach((c) => {
      c(req, res);
    });
    next();
  }
}

// src/app/router.js
const {readFileBytes} = require("fs");
const favicon = readFileBytes("../static/favicon.ico");
Router.get("/json", function(req, res) {
  let data = {
    username: "rw3iss",
    something: "test"
  };
  res.json(data);
});
Router.get("/", function(req, res) {
  res.html("<h2>Home!</h2>");
});
Router.get("/favicon.ico", function(req, res) {
  return favicon != -1 ? res.favicon(favicon) : res.error(new Error("favicon not found"));
});
var router_default = Router;

// src/app/server.js
const {log: log2} = require_log();
const config = {
  ADDRESS: "127.0.0.1",
  PORT: 8080,
  SERVER_NAME: "my-server",
  MAXHEADERS: 4096,
  BUFFER_SIZE: 65536,
  MONITOR: false,
  NO_DELAY: true,
  KEEP_ALIVE: true,
  REUSE_PORT: true,
  REUSE_ADDRESS: true
};
let app = new JustWebApplication(config);
app.use(router_default);
app.start();
