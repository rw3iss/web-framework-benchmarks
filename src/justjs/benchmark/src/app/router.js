import Router from '../lib/router';
const { readFileBytes } = require('fs'); // built-in

const favicon = readFileBytes('../static/favicon.ico');

Router.get('/json', function(req, res) {
    let data = {
        username: "rw3iss",
        something: "test"
    };
    res.json(data);
});

Router.get('/', function(req, res) {
    res.html('<h2>Home!</h2>');
});

Router.get('/favicon.ico', function(req, res) {
    return favicon != -1 ? res.favicon(favicon) : res.error(new Error("favicon not found"));
});

export default Router;