//import { getHttpPhrase } from './utils/httpcodes';

// TODO: Add status code support

function Response(socket) {
    this.socket = socket;
    return this;
}

Response.prototype.html = function(html, status = 200) {
    if (this.socket.html(html) < 0) just.error((new SystemError('sock.html')).stack)
    this.socket.close();
};

Response.prototype.text = function(text, status = 200) {
    if (this.socket.text(text) < 0) just.error((new SystemError('sock.text')).stack)
    this.socket.close();
};

Response.prototype.json = function(object, status = 200) {
    let jm = JSON.stringify(object); // todo: use safe-stringify?
    if (this.socket.json(jm) < 0) just.error((new SystemError('sock.json')).stack)
    this.socket.close();
}

Response.prototype.favicon = function(favicon) {
    if (this.socket.favicon(favicon) < 0) just.error((new SystemError('sock.favicon')).stack)
    this.socket.close();
}

// Todo: add status code support
Response.prototype.error = function(error, status = 500) {
    if (this.socket.error(error) < 0) just.error((new SystemError('sock.error')).stack)
    this.socket.close();
}

// Todo: necessary?
Response.prototype.end = function(status = 200) {
    this.text('', status);
}

function createResponse(socket) {
    return new Response(socket);
}

module.exports = { createResponse }
