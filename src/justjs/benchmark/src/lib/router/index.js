import TrieRouter from './lib/index';
import Middleware from '../middleware';
import url from '../../../node_modules/url'; // todo: find better implementation or don't use library
const { print } = just;

const router = new TrieRouter();

export default class Router extends Middleware {
    
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

    // For internal use only
    static handleRequest(req, res, next) {
        //print("Router::handleRequest: " + req.url);
        // todo: find more efficient implementation of url.parse
        var match = router.match(url.parse(req.url).pathname)
        if (!match) {
            print("404: " + req.url);
            return next();
        }

        // optional:
        // req.param = match.param
        // req.label = match.node.label

        var node = match.node
        var callbacks = node[req.method]
        if (!callbacks) {
            print("405...");
            return;
        }

        // Todo: execute as a stack, in series...
        callbacks.forEach(c => {
            c(req, res);
        });

        //async.series(callbacks, next)

        next();
    }
}